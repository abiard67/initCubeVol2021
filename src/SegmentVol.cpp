/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SegmentVol.cpp
 * Author: snir2g1
 * 
 * Created on 21 mars 2019, 16:25
 */
#include <iostream>

#include "../defs/SegmentVol.h"

using namespace std;

SegmentVol::SegmentVol() {
    horloge = new Horloge();
    temperature = new Temperature();
    batterie = new Batterie();
    emetteurRecepteur = new EmetteurRecepteur();
    mission = new Mission();
    ordinateur = new Ordinateur();
    etat = new Etat();
    segmentSol = new SegmentSol(this);
    reboot = new Reboot();
    surveillance = new Surveillance();
    sauvegarde = new Sauvegarde();
    intialisationInstrument();



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
    sauvegarde->enregistrerMesure();
    reboot->setNumber(reboot->getNumber() + 1);
    reboot->setDateHour(horloge->getDateHeure());
    reboot->systemeReboot();
    // Codage d'envoi vers Segment Sol � faire?
}

void SegmentVol::lancerMission() {
    short interval = mission->getPeriodicity();
    etatThread = true;

    while (etatThread) {
        this_thread::sleep_for(chrono::minutes(interval));
        activerInstrument();
        instrument->obtenirMeusure(2);
        horloge->lire();
        instrument->setDateMesure(horloge->getDateHeure());
        desactiverInstrument();
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
	cout << "ici" << endl;
	        if (appareil.begin() == appareil.end()) {
            cout << "Là" << endl;
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
                segmentSol->envoieACK("ERROR-20");
            }
        }
        if (*it == TypeAppareil::INSTRUMENT) {
            instrument->obtenirStatus();
            if (instrument->obtenirStatus() == -1) {
                segmentSol->envoieACK("ERROR-21");
            }
        }
        if (*it == TypeAppareil::BATTERIE) {
            batterie->obtenirStatus();
            if (batterie->obtenirStatus() == -1) {
                segmentSol->envoieACK("ERROR-22");
            }
        }
        if (*it == TypeAppareil::CUBE) {
            temperature->recupTempSys();
            if (temperature->recupTempSys() == -1) {
                segmentSol->envoieACK("ERROR-23");
            }
        } else
            segmentSol->envoieACK("ERROR-E12");
    }
    activerModuleEmission();
    segmentSol->envoyerStatus(appareil);
}

void SegmentVol::obtenirStatus() {
    short intervale = etat->getPeriodicity();
    while (true) {
        this_thread::sleep_for(chrono::minutes(intervale));
        ordinateur->obtenirStatus();
        instrument->obtenirStatus();
        batterie->obtenirStatus();
        horloge->lire();
        temperature->recupTempSys();
        activerModuleEmission();
        // segmentSol->envoyerStatus();
    }
}

void SegmentVol::effectuerMesure(string mesure) {
    if (mesure == TypeMisEtat::TEMPCELSIUS) {
        activerInstrument();
        instrument->obtenirMeusure(2);
        horloge->lire();
        instrument->setDateMesure(horloge->getDateHeure());
        desactiverInstrument();
    } else if (mesure == TypeMisEtat::PIXEL) {
        activerInstrument();
        instrument->obtenirMeusure();
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

CameraIR* SegmentVol::getCameraIR() {
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

char SegmentVol::intialisationInstrument() {

    stringstream ss;

    vector<int>adrI2C(0);
    string adrConfig;
    string typeConfig;
    vector<int>::iterator itAdrI2C = adrI2C.begin();
    int adrInstrument = 0;
    int iAdrConfig;
    int iTypeConfig;


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
    close(N);


    //Lecture de l'adresse de l'instrument
    XMLDocument config;
    config.LoadFile("../config/initcube.xml");

    XMLText* adrNode = config.FirstChildElement("initcube")->FirstChildElement("instrument")->FirstChildElement("description")->FirstChildElement("adresse")->FirstChild()->ToText();
    adrConfig = adrNode->Value();
    XMLText* typeNode = config.FirstChildElement("initcube")->FirstChildElement("instrument")->FirstChildElement("description")->FirstChildElement("type")->FirstChild()->ToText();
    typeConfig = typeNode->Value();

    ss << adrConfig;
    ss >> hex>>iAdrConfig;

    //Comparaison des adresses
    while (*itAdrI2C != adrI2C.back()) {
        if (*itAdrI2C != iAdrConfig) {
            advance(itAdrI2C, 1);
        } else {
            adrInstrument = *itAdrI2C;
        }

    }
    switch (adrInstrument) {
        case 0: return -1;
        case 0x69:
            /*       Magnetometre* magneto = new Magnetometre();
                   magneto->PassThrough();
                   delete magneto;

                   int I2C = open("/dev/i2c-1", O_RDWR);
                   ioctl(I2C, I2C_SLAVE, 0x0C);
                   if (write(I2C, "", 1) == 1) {
                       adrInstrument = 0x0C;
                       if (typeConfig != "magnetometre") {
                           return -1;
                       }
                       instrument = new Magnetometre();
                   }
                   close(I2C);
             */ if (typeConfig != "camera infrarouge") {
                return -1;
            }
            instrument = new CameraIR();

            break;

            /*  case 0x30:
                   if (typeConfig != "camera phto") {
                       return -1;
                   }
                   instrument = new CameraPhoto();
                   break;
             */
    }




    return 0;
}
