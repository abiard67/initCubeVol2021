#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <thread>
#include "../defs/FrameManager.h"
#include "../defs/serialib.h"
#include "../defs/Status.h"
#include "../defs/Commande.h"

using namespace std;

string FrameManager::ERR_CHECKSUM = "ERR_C";
string FrameManager::ERR_FORMAT = "ERR_F";

int FrameManager::pause = 1000;

FrameManager::FrameManager() {
    commande = new Commande();
	this->message = new Message();
}

FrameManager::FrameManager(const FrameManager& orig) {
}

FrameManager::~FrameManager() {
}

int FrameManager::getNbrePaquets() {
    return this->nbrePaquets;
}

int FrameManager::getNumPaquet() {
    return this->numPaquet;
}

list<vector<char>> FrameManager::getReceived() {
    return this->received;
}

void FrameManager::setTableau(char laDataRecu[100]) {
    for (int i = 0; i < 100; i++) {
        this->tableau[i] = laDataRecu[i];
    }
}

void FrameManager::calculerChecksum(char trame[104], char & PF, char & pf) {
  short Checksum = 0;
  char leChecksum[2];

  for (int i = 0; i < trame[1] + 2; i++) {
      Checksum = Checksum^trame[i];
  }
  sprintf(leChecksum, "%2X", Checksum);
  if (leChecksum[0] == 32) leChecksum[0] = '0';
  if (leChecksum[1] == 32) leChecksum[1] = '0';
  PF = leChecksum[0];
  pf = leChecksum[1];

}

void FrameManager::detramerCommande() {

  extrairenbOctectsDataRecu(trameReception);
  cout << "Nb d'octets du PDU : " << commande->getnbOctectsDataRecu() << endl;
  extraireCommande(trameReception);
  cout << "Type de Commande : " << commande->getCode() << endl;
  extraireParametres(trameReception);
  cout << "Paramètres : " << commande->getParametres() << endl;

}


void FrameManager::extrairenbOctectsDataRecu(char reception[]) {

  int nbdata = (int) reception[1];
  commande->setnbOctectsDataRecu(nbdata);
}

void FrameManager::extraireCommande(char reception[]) {

    vector <char> trame(0);
    for (int i = 0; i <= 104; i++) {

        trame.push_back(reception[i]);

    }

    vector<char>::iterator it = trame.begin();
    string cmdReception;
    advance(it, 1);
    int nbOctects = *it;
    advance(it, 1);

    for (int i = 0; i != nbOctects && *it != '-'; i++) {

        cmdReception.push_back(*it);
        advance(it, 1);

    }

    commande->setCode(cmdReception);
}

void FrameManager::extraireParametres(char reception[]) {

     vector <char>trame;
    size_t found, found2 ;


    for (int i = 0; i <= reception[1]+2; i++) {
                trame.push_back(reception[i]);

    }

     list<string> parametres;
     list<string> paramValeurs;
     vector<char>::iterator it = trame.begin();

     string arg="";
     char elem ='-';


     if(it!=trame.end()){

        for(it = trame.begin();it!=trame.end();++it){

        if (*it==elem){
          arg=elem;
        do
        {
                it++;
            arg=arg+*(it);
        }
        while((*(it+1)!=elem) &&(it!=trame.end()-2)) ;

          parametres.push_back(arg);
          arg="";

        }
       }
        if(commande->getCode()== TypeCommande::MISSION){
		list<string>::iterator it2;
		for (it2 = parametres.begin(); it2 != parametres.end(); ++it2)
	 	{
			found = ((string)*it2).find(TypeMisEtat::PERIOD);

			if (found!=std::string::npos)

			{
				paramValeurs.push_back(TypeMisEtat::PERIOD);
				paramValeurs.push_back(((string)*it2).substr(found+TypeMisEtat::PERIOD.length(), ((string)*it2).size()));

			}
			else {
				found = ((string)*it2).find(TypeMisEtat::DURATION);
				found2= ((string)*it2).find(TypeMisEtat::DATETIME);
				if ((found!=std::string::npos) && (found!=found2))

				{
					paramValeurs.push_back(TypeMisEtat::DURATION);
					paramValeurs.push_back(((string)*it2).substr(found+TypeMisEtat::DURATION.length(), ((string)*it2).size()));

				}
				else {
					found= ((string)*it2).find(TypeMisEtat::DATETIME);
					if (found!=std::string::npos)

					{
						paramValeurs.push_back(TypeMisEtat::DATETIME);
						paramValeurs.push_back(((string)*it2).substr(found+TypeMisEtat::DATETIME.length(), ((string)*it2).size()));

					}
					else {
						paramValeurs.push_back((string)*it2);
					}
				}
			}
		}


	commande->setParametres(paramValeurs);
        }
        else {
	commande->setParametres(parametres);
	}
     }

}

bool FrameManager::verifierChecksum() {
  char PF;
  char pf;
  char cheksumRecuPF, cheksumRecupf;
  cheksumRecuPF = trameReception[trameReception[1] + 2];
  cheksumRecupf = trameReception[trameReception[1] + 3];
  calculerChecksum(trameReception, PF, pf);
  if ((cheksumRecuPF != PF) || (cheksumRecupf != pf)) return false;
  else return true;
}

unsigned char FrameManager::calculerNombrePaquets(Message * message) {
    list<Mesure*> listeDeMesures = message->getMesures();
    int nbreTotalMesures = listeDeMesures.size();
    if (message->getTypeMission() == TypeMisEtat::TEMPCELSIUS) {
        this->nbrePaquets = nbreTotalMesures / 2;
    }
    return nbrePaquets;
}

/**
 *  /~/id/nbre octets/"MISSION"/nbrepaquets/numPaquet/ Ttemp1/ -DTdate1/ Ttemp2/ -DTdate2/CheksumPF/cheksumpf
 *
 */
void FrameManager::tramerMission(Message* message, int nbrePaquets, int numPaquet) {
  char tab[20] = {};
  char PF;
  char pf;


  unsigned int j;

  Mesure *lamesure;
  list<Mesure*> laListe;
  list<Mesure*>::iterator lIndice;
  string valeurMesure, dateHour;
  stringstream stream;

  //trameEmission[0] = '~';
  trameEmission[0] = message->getIdSegment();
  trameEmission[1] = 98; //Valeur provisoire en attendant la fin de construction du message.
  strcpy(tab, TypeCommande::MISSION.c_str());
  for (j = 0; j < TypeCommande::MISSION.size(); j++) {
      trameEmission[2 + j] = tab[j];
  }

  j = j + 2;

  trameEmission[j] = nbrePaquets;
  j++;
  trameEmission[j] = numPaquet;
  j++;

  strcpy(tab, message->getTypeMission().c_str());

  for (unsigned int k = 0; k < message->getTypeMission().size(); k++) {
      trameEmission[j] = tab[k];
      j++;
  }

  //Pour cet incr�ment, seule la mission temp�rature peut �tre lanc�e
  if (message->getTypeMission() == TypeMisEtat::TEMPCELSIUS) {
      laListe = message->getMesures();

      /*************** Traitement de la premi�re donn�e ********************/
      trameEmission[j] = ' ';
      j++;
      strcpy(tab, TypeMisEtat::TEMPERATURE.c_str());
      for (unsigned int k = 0; k < TypeMisEtat::TEMPERATURE.size(); k++) {
          trameEmission[j] = tab[k];
          j++;
      }

      lIndice = laListe.begin();
      lamesure = *lIndice; //On met dans la variable lamesure le contenu de l'it�rateur
      stream << fixed << setprecision(1) << lamesure->getMesure();
      valeurMesure = stream.str();
      strcpy(tab, valeurMesure.c_str());
      for (unsigned int k = 0; k < valeurMesure.size(); k++) {
          trameEmission[j] = tab[k];
          j++;
      }
      trameEmission[j] = ' ';
      j++;
      strcpy(tab, TypeMisEtat::DATETIME.c_str());
      for (unsigned int k = 0; k < TypeMisEtat::DATETIME.size(); k++) {
          trameEmission[j] = tab[k];
          j++;
      }
      dateHour = lamesure->getDateHour();
      strcpy(tab, dateHour.c_str());
      for (unsigned int k = 0; k < dateHour.size(); k++) {
          trameEmission[j] = tab[k];
          j++;
      }
      laListe.pop_front(); //On supprime la donn�e trait�e

      /*************** Traitement de la deuxi�me donn�e ********************/
      trameEmission[j] = ' ';
      j++;
      strcpy(tab, TypeMisEtat::TEMPERATURE.c_str());
      for (unsigned int k = 0; k < TypeMisEtat::TEMPERATURE.size(); k++) {
          trameEmission[j] = tab[k];
          j++;
      }

      lIndice = laListe.begin();
      lamesure = *lIndice; //On met dans la variable lamesure le contenu de l'it�rateur
      stream.str(""); //On vide le flux
      stream << fixed << setprecision(1) << lamesure->getMesure();
      valeurMesure = stream.str();
      strcpy(tab, valeurMesure.c_str());
      for (unsigned int k = 0; k < valeurMesure.size(); k++) {
          trameEmission[j] = tab[k];
          j++;
      }
      trameEmission[j] = ' ';
      j++;
      strcpy(tab, TypeMisEtat::DATETIME.c_str());
      for (unsigned int k = 0; k < TypeMisEtat::DATETIME.size(); k++) {
          trameEmission[j] = tab[k];
          j++;
      }
      dateHour = lamesure->getDateHour();
      strcpy(tab, dateHour.c_str());
      for (unsigned int k = 0; k < dateHour.size(); k++) {
          trameEmission[j] = tab[k];
          j++;
      }
      laListe.pop_front();

      /** Mise � jour de la liste **/
      message->setMesures(laListe);
  }

  /** Mise � jour du champ "nombre d'octets" **/
  trameEmission[1] = j - 2; //ATTENTION A VERIFIER

  calculerChecksum(trameEmission,PF, pf);
  trameEmission[j] = PF;
  j++;
  trameEmission[j] = pf;
  j++;
  trameEmission[j] = 255;
  j++;
  for (j = j; j < 100; j++)
      trameEmission[j] = 0;


}

void FrameManager::ajouterDataOrdiBord(Message* amessage, unsigned int &aposition) {
    char tab[20] = {};
    strcpy(tab, TypeAppareil::ORDIBORD.c_str());
    for (unsigned int k = 0; k < TypeAppareil::ORDIBORD.size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, TypeMisEtat::STOCKMO.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::STOCKMO.size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, amessage->getMicroSDenMo().c_str());
    for (unsigned int k = 0; k < amessage->getMicroSDenMo().size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }

    strcpy(tab, TypeMisEtat::RAMPOURCENT.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::RAMPOURCENT.size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, amessage->getRAMenPourcent().c_str());
    for (unsigned int k = 0; k < amessage->getRAMenPourcent().size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    trameEmission[aposition] = ' ';
    aposition++;
    strcpy(tab, TypeMisEtat::TEMPERATURE.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::TEMPERATURE.size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }

    strcpy(tab, amessage->getTemperatureProc().c_str());
    for (unsigned int k = 0; k < amessage->getTemperatureProc().size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    trameEmission[aposition] = ' ';
    aposition++;
    strcpy(tab, TypeMisEtat::DATETIME.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::DATETIME.size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, amessage->getDateOrdinateur().c_str());
    for (unsigned int k = 0; k < amessage->getDateOrdinateur().size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
}

void FrameManager::ajouterDataBattery(Message* amessage, unsigned int &aposition) {
    char tab[20] = {};
    strcpy(tab, TypeAppareil::BATTERIE.c_str());
    for (unsigned int k = 0; k < TypeAppareil::BATTERIE.size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, TypeMisEtat::CHARGE.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::CHARGE.size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, amessage->getChargeBat().c_str());
    for (unsigned int k = 0; k < amessage->getChargeBat().size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, TypeMisEtat::VOLTAGE.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::VOLTAGE.size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, amessage->getVoltageBat().c_str());
    for (unsigned int k = 0; k < amessage->getVoltageBat().size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, TypeMisEtat::AMPERAGE.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::AMPERAGE.size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, amessage->getAmperageBat().c_str());
    for (unsigned int k = 0; k < amessage->getAmperageBat().size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    if (amessage->getChargeStatus()) {
        strcpy(tab, TypeMisEtat::LOAD.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::LOAD.size(); k++) {
            trameEmission[aposition] = tab[k];
            aposition++;
        }
    }

    trameEmission[aposition] = ' ';
    aposition++;
    strcpy(tab, TypeMisEtat::TEMPERATURE.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::TEMPERATURE.size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, amessage->getTemperatureBat().c_str());
    for (unsigned int k = 0; k < amessage->getTemperatureBat().size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    trameEmission[aposition] = ' ';
    aposition++;
}

void FrameManager::ajouterStatusInst(Message* amessage, unsigned int &aposition) {
    char tab[20] = {};
    strcpy(tab, TypeAppareil::INSTRUMENT.c_str());
    for (unsigned int k = 0; k < TypeAppareil::BATTERIE.size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    Status * leStatus = amessage->getStatInstrument();
    if (leStatus->getOnOff() == true) {
        strcpy(tab, TypeMisEtat::ON.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::ON.size(); k++) {
            trameEmission[aposition] = tab[k];
            aposition++;
        }
    } else {
        strcpy(tab, TypeMisEtat::OFF.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::OFF.size(); k++) {
            trameEmission[aposition] = tab[k];
            aposition++;
        }
    }

    if (leStatus->getMode() == Mode::NORMAL) {
        strcpy(tab, TypeMisEtat::NORMAL.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::NORMAL.size(); k++) {
            trameEmission[aposition] = tab[k];
            aposition++;
        }
    } else if (leStatus->getMode() == Mode::SLEEP) {
        strcpy(tab, TypeMisEtat::SLEEP.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::SLEEP.size(); k++) {
            trameEmission[aposition] = tab[k];
            aposition++;
        }
    } else if (leStatus->getMode() == Mode::STAND_BY) {
        strcpy(tab, TypeMisEtat::STANDBY.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::STANDBY.size(); k++) {
            trameEmission[aposition] = tab[k];
            aposition++;
        }
    }

    trameEmission[aposition] = ' ';
    aposition++;
    strcpy(tab, TypeMisEtat::TEMPERATURE.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::TEMPERATURE.size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    stringstream stream;
    stream << fixed << setprecision(1) << leStatus->getTemp();
    strcpy(tab, stream.str().c_str());
    for (unsigned int k = 0; k < stream.str().size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    trameEmission[aposition] = ' ';
    aposition++;
}

void FrameManager::ajouterStatusCube(Message* amessage, unsigned int &aposition) {
    char tab[20] = {};

    strcpy(tab, TypeAppareil::CUBE.c_str());
    for (unsigned int k = 0; k < TypeAppareil::CUBE.size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }
    trameEmission[aposition] = ' ';
    aposition++;

    strcpy(tab, TypeMisEtat::TEMPERATURE.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::TEMPERATURE.size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }

    strcpy(tab, amessage->getTemperatureCube().c_str());

    for (unsigned int k = 0; k < amessage->getTemperatureCube().size(); k++) {
        trameEmission[aposition] = tab[k];
        aposition++;
    }

    trameEmission[aposition] = ' ';
    aposition++;

    if (amessage->getReboot()->getNumber() > 0) {
        strcpy(tab, TypeAppareil::REBOOT.c_str());
        for (unsigned int k = 0; k < TypeAppareil::REBOOT.size(); k++) {
            trameEmission[aposition] = tab[k];
            aposition++;
        }

        strcpy(tab, TypeMisEtat::DATETIME.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::DATETIME.size(); k++) {
            trameEmission[aposition] = tab[k];
            aposition++;
        }

        strcpy(tab, amessage->getReboot()->getDateHour().c_str());
        for (unsigned int k = 0; k < amessage->getReboot()->getDateHour().size(); k++) {
            trameEmission[aposition] = tab[k];
            aposition++;
        }

        strcpy(tab, TypeMisEtat::REBOOT_NUMBER.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::REBOOT_NUMBER.size(); k++) {
            trameEmission[aposition] = tab[k];
            aposition++;
        }

        strcpy(tab, to_string(amessage->getReboot()->getNumber()).c_str());
        for (unsigned int k = 0; k < to_string(amessage->getReboot()->getNumber()).size(); k++) {
            trameEmission[aposition] = tab[k];
            aposition++;

        }
    }

}

/**
 *  /~/id/nbre octets/"STATUS"/nbrepaquets/numPaquet/................../CheksumPF/cheksumpf/255
 *  /~/id/nbre octets/"STATUS"/2	1	/-BORD/-SMo/-S6553/ -T47/ -DT2019/02/13 12:12:36/-BATT/-C85/-V4,1/-A950/-LOAD/ -T25,0 /CheksumPF/cheksumpf/255
 *  /~/id/nbre octets/"STATUS"/2	2	/-INST/-ON/-STBY60/ -T25,8/ -CUBE/ -T26,4 /-REBOOT/-DT2019/02/13 12:12:36/-N1/CheksumPF/cheksumpf/255
 *
 */
void FrameManager::tramerStatus(Message* message, int nbrePaquets, int numPaquet) {
  char tab[20] = {};
      char PF;
      char pf;
      unsigned int j;

      string valeurMesure, dateHour;
      stringstream stream;

  //    trameEmission[0] = '~';
      trameEmission[0] = message->getIdSegment();
      trameEmission[1] = 98; //Valeur provisoire en attendant la fin de construction du message.
      strcpy(tab, TypeCommande::STATUS.c_str());
      for (j = 0; j < TypeCommande::STATUS.size(); j++) {
          trameEmission[2 + j] = tab[j];
      }
      j = j + 2;
      trameEmission[j] = nbrePaquets;
      j++;
      trameEmission[j] = numPaquet;
      j++;
      if (numPaquet == 1) {
          ajouterDataOrdiBord(message, j);
          ajouterDataBattery(message, j);
      } else {
          ajouterStatusInst(message, j);
          ajouterStatusCube(message, j);
      }

      /** Mise � jour du champ "nombre d'octets" **/
      trameEmission[1] = j - 2; //ATTENTION A VERIFIER

      calculerChecksum(trameEmission,PF, pf);
      trameEmission[j] = PF;
      j++;
      trameEmission[j] = pf;
      j++;
      trameEmission[j] = 255;
      j++;
      for (j = j; j < 100; j++)
          trameEmission[j] = 0;

}

void FrameManager::tramerStatus(Message* message, list<string> appareils, int nbrePaquets, int numPaquet) {
  char tab[20] = {};
  char PF;
  char pf;
  unsigned int j;

  string valeurMesure, dateHour;
  stringstream stream;


  //trameEmission[0] = '~';
  trameEmission[0] = message->getIdSegment();
  trameEmission[1] = 98; //Valeur provisoire en attendant la fin de construction du message.
  strcpy(tab, TypeCommande::STATUS.c_str());
  for (j = 0; j < TypeCommande::STATUS.size(); j++) {
      trameEmission[2 + j] = tab[j];
  }
  j = j + 2;
  trameEmission[j] = nbrePaquets;
  j++;
  trameEmission[j] = numPaquet;
  j++;

  if (appareils.empty())
      if (numPaquet == 1) {
          ajouterDataOrdiBord(message, j);
          ajouterDataBattery(message, j);
      } else {
          ajouterStatusInst(message, j);
          ajouterStatusCube(message, j);
      } else {
      if (numPaquet == 1) {
          if (message->getMicroSDenMo() != "0") ajouterDataOrdiBord(message, j);
          else if (message->getVoltageBat() != "0") ajouterDataBattery(message, j);
          else if (message->getStatInstrument()->getTemp() != 0) ajouterStatusInst(message, j);
          else if (message->getTemperatureCube() != "0") ajouterStatusCube(message, j);
          else if ((message->getTemperatureCube() == "0") && (message->getReboot()->getNumber() != 0)) {
              strcpy(tab, TypeAppareil::REBOOT.c_str());
              for (unsigned int k = 0; k < TypeAppareil::REBOOT.size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;
              }

              strcpy(tab, TypeMisEtat::DATETIME.c_str());
              for (unsigned int k = 0; k < TypeMisEtat::DATETIME.size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;
              }

              strcpy(tab, message->getReboot()->getDateHour().c_str());
              for (unsigned int k = 0; k < message->getReboot()->getDateHour().size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;
              }

              strcpy(tab, TypeMisEtat::REBOOT_NUMBER.c_str());
              for (unsigned int k = 0; k < TypeMisEtat::REBOOT_NUMBER.size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;
              }

              strcpy(tab, to_string(message->getReboot()->getNumber()).c_str());
              for (unsigned int k = 0; k < to_string(message->getReboot()->getNumber()).size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;

              }
          }
      } else if (numPaquet == 2) {
          if (message->getVoltageBat() != "0") ajouterDataBattery(message, j);
          else if (message->getStatInstrument()->getTemp() != 0) ajouterStatusInst(message, j);
          else if (message->getTemperatureCube() != "0") ajouterStatusCube(message, j);
          else if ((message->getTemperatureCube() == "0") && (message->getReboot()->getNumber() != 0)) {
              strcpy(tab, TypeAppareil::REBOOT.c_str());
              for (unsigned int k = 0; k < TypeAppareil::REBOOT.size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;
              }

              strcpy(tab, TypeMisEtat::DATETIME.c_str());
              for (unsigned int k = 0; k < TypeMisEtat::DATETIME.size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;
              }

              strcpy(tab, message->getReboot()->getDateHour().c_str());
              for (unsigned int k = 0; k < message->getReboot()->getDateHour().size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;
              }

              strcpy(tab, TypeMisEtat::REBOOT_NUMBER.c_str());
              for (unsigned int k = 0; k < TypeMisEtat::REBOOT_NUMBER.size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;
              }

              strcpy(tab, to_string(message->getReboot()->getNumber()).c_str());
              for (unsigned int k = 0; k < to_string(message->getReboot()->getNumber()).size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;

              }
          }
      } else if (numPaquet == 3) {
          if (message->getStatInstrument()->getTemp() != 0) ajouterStatusInst(message, j);
          else if (message->getTemperatureCube() != "0") ajouterStatusCube(message, j);
          else if ((message->getTemperatureCube() == "0") && (message->getReboot()->getNumber() != 0)) {
              strcpy(tab, TypeAppareil::REBOOT.c_str());
              for (unsigned int k = 0; k < TypeAppareil::REBOOT.size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;
              }

              strcpy(tab, TypeMisEtat::DATETIME.c_str());
              for (unsigned int k = 0; k < TypeMisEtat::DATETIME.size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;
              }

              strcpy(tab, message->getReboot()->getDateHour().c_str());
              for (unsigned int k = 0; k < message->getReboot()->getDateHour().size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;
              }

              strcpy(tab, TypeMisEtat::REBOOT_NUMBER.c_str());
              for (unsigned int k = 0; k < TypeMisEtat::REBOOT_NUMBER.size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;
              }

              strcpy(tab, to_string(message->getReboot()->getNumber()).c_str());
              for (unsigned int k = 0; k < to_string(message->getReboot()->getNumber()).size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;

              }
          }
      } else if (numPaquet == 4) {
          if (message->getTemperatureCube() != "0") ajouterStatusCube(message, j);
          else if ((message->getTemperatureCube() == "0") && (message->getReboot()->getNumber() != 0)) {
              strcpy(tab, TypeAppareil::REBOOT.c_str());
              for (unsigned int k = 0; k < TypeAppareil::REBOOT.size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;
              }

              strcpy(tab, TypeMisEtat::DATETIME.c_str());
              for (unsigned int k = 0; k < TypeMisEtat::DATETIME.size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;
              }

              strcpy(tab, message->getReboot()->getDateHour().c_str());
              for (unsigned int k = 0; k < message->getReboot()->getDateHour().size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;
              }

              strcpy(tab, TypeMisEtat::REBOOT_NUMBER.c_str());
              for (unsigned int k = 0; k < TypeMisEtat::REBOOT_NUMBER.size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;
              }

              strcpy(tab, to_string(message->getReboot()->getNumber()).c_str());
              for (unsigned int k = 0; k < to_string(message->getReboot()->getNumber()).size(); k++) {
                  trameEmission[j] = tab[k];
                  j++;

              }
          }
      }
	}

    /** Mise � jour du champ "nombre d'octets" **/
    trameEmission[1] = j - 2; //ATTENTION A VERIFIER

    calculerChecksum(trameEmission,PF, pf);
    trameEmission[j] = PF;
    j++;
    trameEmission[j] = pf;
    j++;
    trameEmission[j] = 255;
    j++;
    for (j = j; j < 100; j++)
        trameEmission[j] = 0;

}


void FrameManager::tramerMesure(Message* message, int nbrePaquets, int numPaquet) {

      list<string>::iterator lIndice;
      char tab[20] = {};
      char PF;
      char pf;
      unsigned int j = 0, nbrePixels = 0;

  //    trameEmission[0] = '~';
      trameEmission[0] = message->getIdSegment();
      trameEmission[1] = 98; //Valeur provisoire en attendant la fin de construction du message.

      strcpy(tab, TypeCommande::MEASURE.c_str());
      for (j = 0; j < TypeCommande::MEASURE.size(); j++) {
          trameEmission[2 + j] = tab[j];
      }

      j = j + 2;

      trameEmission[j] = nbrePaquets;
      j++;
      trameEmission[j] = numPaquet;
      j++;

      strcpy(tab, message->getTypeMesure().c_str());

      for (unsigned int k = 0; k < message->getTypeMesure().size(); k++) {
          trameEmission[j] = tab[k];
          j++;
      }
      if (message->getTypeMesure() == TypeMisEtat::PIXEL) {
          list<string> lesPixels = message->getPixels();

          for (lIndice = lesPixels.begin(); lIndice != lesPixels.end(); lIndice++) {
              trameEmission[j] = ' ';
              j++;
              //cout<< (*lIndice) << " ";
              strcpy(tab, (*lIndice).c_str());
              for (unsigned int k = 0; k < (*lIndice).size(); k++) {
                  trameEmission[j] = tab[k];

                  j++;
              }
              //lesPixels.erase(lIndice);

              //--lIndice;

              nbrePixels = nbrePixels + 1;

              if (nbrePixels == 8) break; // sortie tous les 8 pixels.

          }
          lesPixels.erase(lesPixels.begin(), lIndice);
          message->setPixels(lesPixels);
      } else if (message->getTypeMesure() == TypeMisEtat::TEMPCELSIUS) {
          list<Mesure*> mesures = message->getMesures();

          float releve = mesures.back()->getMesure();
          stringstream stream;
          stream << fixed << setprecision(1) << releve;

          strcpy(tab, (stream.str()).c_str());
          trameEmission[j] = ' ';
          j++;
          for (unsigned int k = 0; k < (stream.str()).size(); k++) {
              trameEmission[j] = tab[k];
              j++;
          }
      }
      trameEmission[j] = ' ';

      j++;
      trameEmission[1] = j - 2; //ATTENTION A VERIFIER

      calculerChecksum(trameEmission,PF, pf);
      trameEmission[j] = PF;

      j++;
      trameEmission[j] = pf;

      j++;
      trameEmission[j] = 255;
      j++;
      for (j = j; j < 100; j++)
          trameEmission[j] = 0;
}

string FrameManager::extraireTypeMessage(int &pos) {
    string typeMessage = "";
    bool OK = false;
    int i;

    i = 0;
    for (vector<char>::iterator it = (received.front()).begin(); it != (received.front()).end(); ++it) {
        if ((i == 0)&&(*it == '~')) {
            OK = true;
        }
        if (OK == true) {
            tableau[i] = *it;
            i = i + 1;
            if (i == 100) break;
        }
    }
    //if ((received.front()).front()=='~')
    //{
    //}
    if (tableau[0] == '~') {
        OK = verifierChecksum();
        if (!OK) return FrameManager::ERR_CHECKSUM;
        for (i = 3; i < 11; i++) {
            if ((tableau[i] > 0x41) && (tableau[i] < 0x7A)) typeMessage = typeMessage + tableau[i];
            else {
                pos = i;
                break;
            }
        }
        extraireNombrePaquets(pos);
        return typeMessage;
    } else return FrameManager::ERR_FORMAT;
}

void FrameManager::extraireNombrePaquets(int &pos) {
    this->nbrePaquets = tableau[pos];
    this->numPaquet = tableau[pos + 1];
    pos = pos + 2;
}

int FrameManager::calculerNbrePaquetsSalve() {
    return received.size();
}

string FrameManager::extraireTypeDataMission(int &pos) {
    int i;
    string typeDataMission = "-";
    for (i = pos; i < pos + 7; i++) {
        if ((tableau[i] > 0x41) && (tableau[i] < 0x7A)) typeDataMission = typeDataMission + tableau[i];
        if (((i != pos)&&(tableau[i] == '-')) || (tableau[i] == ' ')) {
            pos = i;
            break;
        }
    }
    if (typeDataMission.size() == 1) return FrameManager::ERR_FORMAT;
    else return typeDataMission;
}

void FrameManager::addReceived(char recu [100]) {
    vector<char> uneTrame(recu, recu + 100);
    received.push_back(uneTrame);
}

void FrameManager::supprimerPaquet() {
    this->received.pop_front();
}

vector<char> FrameManager::tramerRepAcq(Message* message, string ReponseAcquitement) {


    vector<char> trameRepAcq(0);
    int j=0;
    char tableauRepAcq[100];
	char PF,pf;
	short Checksum = 0;
    char leChecksum[2];

	trameRepAcq.push_back( message->getIdSegment());

	strcpy(tableauRepAcq, ReponseAcquitement.c_str());
    for (j = 0; j < (int)ReponseAcquitement.size(); j++) {
        trameRepAcq.push_back( tableauRepAcq[j]);
    }

	for (int i = 1; i < (int)trameRepAcq.size(); i++) {
        Checksum = Checksum^tableauRepAcq[i];
    }
    sprintf(leChecksum, "%2X", Checksum);
    if (leChecksum[0] == 32) leChecksum[0] = '0';
    if (leChecksum[1] == 32) leChecksum[1] = '0';
    PF = leChecksum[0];
    pf = leChecksum[1];

	trameRepAcq.push_back( PF);
	trameRepAcq.push_back( pf);
	trameRepAcq.push_back( 255);
	return trameRepAcq;

}
