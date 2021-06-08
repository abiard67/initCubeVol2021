#include <iostream>

#include "../defs/SegmentVol.h"

using namespace std;
using namespace std::chrono ;
SegmentVol::SegmentVol() {
    horloge = new Horloge();
    temperature = new Temperature();
    batterie = new Batterie();
    emetteurRecepteur = new EmetteurRecepteur();
    mission = new Mission();
    ordinateur = new Ordinateur();
    etat = new Etat();
    segmentSol = new SegmentSol(this);
    surveillance = new Surveillance(this);
    sauvegarde = new Sauvegarde();
    this->intialisationInstrument();
}

SegmentVol::~SegmentVol() {
}

thread SegmentVol::tLancerMission() {
    return thread([this] {
        lancerMission();
    });
}

thread SegmentVol::tArretMission() {
    return thread([this] {
        arretMission();
    });
}

thread SegmentVol::tSurveillerConstantes() {
    return thread([this] {
        surveillerConstantes();
    });
}

void SegmentVol::surveillerConstantes() {
    surveillance->surveillerConstantes();
}

void SegmentVol::demandeManuelleReboot() {
	sauvegarde->enregistrerMesures(this->instrument->getMesures());
	ordinateur->getReboot()->setNumber(ordinateur->getReboot()->getNumber() + 1);
    ordinateur->getReboot()->setDateHour(horloge->getDateHeure());
    ordinateur->getReboot()->systemeReboot();
}

void SegmentVol::lancerMission() {
    short interval = mission->getPeriodicity();
    string startTime = mission->getStartTime(); // on initialise le debut
    string measureType = mission->getMeasureType(); // le type de measure a voir avec richard
    etatThread = true;
    istringstream iss; // On crée le flux
    if (startTime != "") { // si il n'y a pas de debut on envoie directement les informations

        size_t pos = startTime.find('/'); // on trouve le premier "/"

        int year, month, day, hour, minute, second;
        iss = istringstream(startTime.substr(0, pos)); //iss = On récuperer l'info avant le premier "/"
        iss>>year; // on le stock dans int year

        tm timeinfo = tm(); //timeinfo = https://www.cplusplus.com/reference/ctime/tm/
        timeinfo.tm_year = year - 1900; // On suit le protocole de timeinfo

        ///////////////////////////////////////////////////////////////
        string leReste = startTime.substr(pos + 1); // on déclare "leReste" = ce qui a apres "/"
        pos = leReste.find('/'); // on trouve "/" suivant

        iss = istringstream(leReste.substr(0, pos)); // iss = premier arguments apres "/"
        iss>>month; //on stock le mois

        timeinfo.tm_mon = month - 1; // month: january

        ////////////////////////////////////////////////////////////////

        leReste = leReste.substr(pos + 1);
        pos = leReste.find(' '); // on cherche l'espace

        iss = istringstream(leReste.substr(0, pos)); //
        iss>>day; //on stock le jour

        timeinfo.tm_mday = day; // day: 1st

        ///////////////////////////////////////////////////////////////

        leReste = leReste.substr(pos + 1);
        pos = leReste.find(':'); // on trouve le premier ":"

        iss = istringstream(leReste.substr(0, pos));
        iss>>hour; // on stock l'heure

        timeinfo.tm_hour = hour;

        /////////////////////////////////////////////////////////////

        leReste = leReste.substr(pos + 1);
        pos = leReste.find(':'); // le suivant ":"
        iss = istringstream(leReste.substr(0, pos));
        iss>>minute; // on stock les secondes
        timeinfo.tm_min = minute; //

        ////////////////////////////////////////////////////////////

        iss = istringstream(leReste.substr(pos + 1, 2));
        iss>>second; // on termine et on stock les secondes
        timeinfo.tm_sec = second;

        ///////////////////////////////////////////////////////////

        time_t tt = mktime(&timeinfo); //Permet d'ajuster les dates en cas de probleme
        system_clock::time_point tp = system_clock::from_time_t(tt);
        //auto attent = chrono::time_point_cast<std::chrono::seconds>(delay);
        int elapsed_seconds = chrono::duration_cast<chrono::seconds> (tp - system_clock::now()).count(); //l'heure de la mission (tp) - l'heure local du systeme
		system_clock::time_point today = system_clock::now();
		  std::time_t tooooday;
		  tooooday = system_clock::to_time_t ( today );
        if (elapsed_seconds > 0) {
            this_thread::sleep_for(chrono::seconds(elapsed_seconds)); // on attends le nombre de seconds qui est le resultat de la soustration donc elapsed_seconds
        } else {
            segmentSol->envoyerInfos("ERROR-24"); // on revoie un code error si le nombre de seconde est inferieur a 0
            return;
        }

    }

    while (etatThread) {
        thread laFindeMission = this->tArretMission(); // Permet de savoir quand arret la mission donc la duree
        laFindeMission.detach();
        activerInstrument();
        instrument->faireMesure(2);
        horloge->lire();
        instrument->setDateMesure(horloge->getDateHeure());
        desactiverInstrument();
        this_thread::sleep_for(chrono::minutes(interval)); // pause selon les minutes, arretMission
    }
    activerModuleEmission();
    segmentSol->envoyerMission();
}

void SegmentVol::arretMission() {
    short delay = mission->getDuration();
    this_thread::sleep_for(chrono::minutes(delay));
    etatThread = false;
}

void SegmentVol::obtenirStatus(list<string> appareil) {
    list<string>::iterator it;
    horloge->lire();
		list<string>::iterator it2;

	if (appareil.begin() == appareil.end()) {
        ordinateur->obtenirStatus();
        instrument->obtenirStatus();
        batterie->obtenirStatus();
        horloge->lire();
        temperature->recupTempSys();
    }
    else
    for (it = appareil.begin(); it != appareil.end(); it++) {

        if (*it == TypeAppareil::ORDIBORD) {
            ordinateur->obtenirStatus();
            if (ordinateur->obtenirStatus() == -1) {
                segmentSol->envoyerInfos("ERROR-20");
            }
        }
        else if (*it == TypeAppareil::INSTRUMENT) {
            instrument->obtenirStatus();
            if (instrument->obtenirStatus() == -1) {
                segmentSol->envoyerInfos("ERROR-21");
            }
        }
        else if (*it == TypeAppareil::BATTERIE) {
            batterie->obtenirStatus();
            if (batterie->obtenirStatus() == -1) {
                segmentSol->envoyerInfos("ERROR-22");
            }
        }
        else if (*it == TypeAppareil::CUBE) {
            temperature->recupTempSys();
            if (temperature->recupTempSys() == -1) {
                segmentSol->envoyerInfos("ERROR-23");
            }
        }

		else if ((*it != TypeAppareil::ORDIBORD) && (*it != TypeAppareil::INSTRUMENT) &&
			(*it != TypeAppareil::BATTERIE) && (*it != TypeAppareil::CUBE) && (*it!=TypeAppareil::REBOOT))
		{
				segmentSol->envoyerInfos("ERROR-E12");
		}
    }
    activerModuleEmission();
    segmentSol->envoyerStatus(appareil);

}

void SegmentVol::obtenirStatus() {
    short intervale = etat->getPeriodicity();
		list<string> appareil;
    while (true) {
        this_thread::sleep_for(chrono::minutes(intervale));
        ordinateur->obtenirStatus();
        instrument->obtenirStatus();
        batterie->obtenirStatus();
        horloge->lire();
        temperature->recupTempSys();
        activerModuleEmission();
		segmentSol->envoyerStatus(appareil);
        // segmentSol->envoyerStatus(); //////////////////////////////////////////////////////
    }
}

void SegmentVol::effectuerMesure(string mesure) {
    if (mesure == TypeMisEtat::TEMPCELSIUS) {
        activerInstrument();
        instrument->faireMesure(2);
        horloge->lire();
        instrument->setDateMesure(horloge->getDateHeure());
        desactiverInstrument();
    } else if (mesure == TypeMisEtat::PIXEL) {
        activerInstrument();
        instrument->faireMesure();
        desactiverInstrument();
    }
    activerModuleEmission();
    segmentSol->envoyerMesure(mesure);
}

void SegmentVol::creerMission(short periode, short duree, string debut, string type) {

    mission->setDuration(duree);
    mission->setPeriodicity(periode);
    mission->setStartTime(debut);
    mission->setMeasureType(type);
}

void SegmentVol::activerModuleEmission() {

    emetteurRecepteur->activerEmetteur();
}

void SegmentVol::activerInstrument() {

    instrument->activer();
}

void SegmentVol::desactiverInstrument() {

    instrument->desactiver();
}

void SegmentVol::desactiverModuleEmission() {

    emetteurRecepteur->desativerEmetteur();
}

void SegmentVol::configurerRecupEtat(short period, list<string> instrument) {
    etat->setAppareil(instrument);
    etat->setPeriodicity(period);
}

thread SegmentVol::recupEtat() {
    return thread([this] {
        obtenirStatus();
    });
}

Horloge* SegmentVol::getHorloge() {
    return horloge;
}

Temperature* SegmentVol::getTemperature() {
    return temperature;
}

Instrument* SegmentVol::getInstrument() {
    return instrument;
}

Batterie* SegmentVol::getBatterie() {
    return batterie;
}

EmetteurRecepteur* SegmentVol::getEmetteurRecepteur() {
    return emetteurRecepteur;
}

Mission* SegmentVol::getMission() {
    return mission;
}

Ordinateur* SegmentVol::getOrdinateur() {
    return ordinateur;
}

Etat* SegmentVol::getEtat() {
    return etat;
}

unsigned char SegmentVol::getIdentifiant() {
    return identifiant;
}

void SegmentVol::setIdentifiant(unsigned char id) {
    identifiant = id;
}


int SegmentVol::intialisationInstrument() {


    stringstream ss;


    vector<int>adrI2C(0);
    string adrConfig;
    string typeConfig;

    int adrInstrument = 0;
    int iAdrConfig;


    //lecture des adresse I2C
    int N = open("/dev/i2c-1", O_RDWR);

    for (int i = 0x00; i <= 0x77; i++) {
        ioctl(N, I2C_SLAVE, i);

        if (write(N, "", 1) == 1) {
            switch (i) {
                case 0x18: break;
                case 0x04: break;
                case 0x14: break;
                case 0x68: break;
                default: adrI2C.push_back(i);


                    break;
            }
        }
    }
        vector<int>::iterator itAdrI2C = adrI2C.begin();




    close(N);


    //Lecture de l'adresse de l'instrument
    XMLDocument config;
	XMLError anError = config.LoadFile("../config/initcube.xml");
    XMLText* adrNode = config.FirstChildElement("initcube")->FirstChildElement("instrument")->FirstChildElement("description")->FirstChildElement("adresse")->FirstChild()->ToText();
    adrConfig = adrNode->Value();
    XMLText* typeNode = config.FirstChildElement("initcube")->FirstChildElement("instrument")->FirstChildElement("description")->FirstChildElement("type")->FirstChild()->ToText();
    typeConfig = typeNode->Value();
    ss << adrConfig;
    ss >> hex>>iAdrConfig;

    //Comparaison des adresses

   if(*itAdrI2C == adrI2C.back()){
   	adrInstrument = *itAdrI2C;
   }

    else{
    while (*itAdrI2C != adrI2C.back()) {
        if (*itAdrI2C != iAdrConfig) {
            advance(itAdrI2C, 1);

        } else {
            adrInstrument = *itAdrI2C;
               }

    		}
	 	}
    switch (adrInstrument) {
        case 0: return -1;
        case 0x69:
          /*         Magnetometre* magneto = new Magnetometre();
                   magneto->PassThrough();
                   delete magneto;

                   int I2C = open("/dev/i2c-1", O_RDWR);
                   ioctl(I2C, I2C_SLAVE, 0x0C);
                   if (write(I2C, "", 1) == 1) {
                       adrInstrument = 0x0C;
                       if (typeConfig != "magnetometre") {
                           return -1;
                       }
                       //instrument = new Magnetometre();
                   }
                   close(I2C);
              if (typeConfig != "camera infrarouge") {
                return -1;

            }*/

            instrument = new CameraIR();

            break;

            /*  case 0x30:
                   if (typeConfig != "camera photo") {
                       return -1;
                   }
                   instrument = new CameraPhoto();
                   break;
             */

    }




    return 0;
}
int SegmentVol::resetStatus(list<string> appareil)
{
	list<string>::iterator it;
	if (appareil.begin() == appareil.end()) {
		ordinateur->resetStatus();
		instrument->resetStatus();
		batterie->resetStatus();
		ordinateur->getReboot()->resetStatus();
		temperature->resetTemperature();
    }
    else
    for (it = appareil.begin(); it != appareil.end(); it++) {

        if (*it == TypeAppareil::ORDIBORD) {
			ordinateur->resetStatus();
        }
        if (*it == TypeAppareil::INSTRUMENT) {
			instrument->resetStatus();
        }
        if (*it == TypeAppareil::BATTERIE) {
			batterie->resetStatus();
        }
        if (*it == TypeAppareil::CUBE) {
			temperature->resetTemperature();
        }
    }
	return 0;

}
