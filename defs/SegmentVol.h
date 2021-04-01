/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SegmentVol.h
 * Author: snir2g1
 *
 * Created on 21 mars 2019, 16:25
 */

#ifndef SEGMENTVOL_H
#define SEGMENTVOL_H
#include <stdexcept>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <list>
#include <iterator>
#include <thread>
#include "Horloge.h"
#include "Temperature.h"
#include "CameraIR.h"
#include "Batterie.h"
#include "EmetteurRecepteur.h"
#include "Mission.h"
#include "Ordinateur.h"
#include "SegmentSol.h"
#include "Etat.h"
#include "TypeMisEtat.h"
#include "TypeAppareil.h"
#include "Reboot.h"
#include "Surveillance.h"
#include "Sauvegarde.h"
#include "tinyxml2.h"
#include <sstream>
#include "Magnetometre.h"
#include "CameraPhoto.h"

using namespace tinyxml2;
using namespace std;

class SegmentSol;

class SegmentVol : public TypeMisEtat, TypeAppareil {
public:
    SegmentVol();
    virtual ~SegmentVol();
    void lancerMission();
    void arretMission();
    void obtenirStatus(list<string> appareil);
    void obtenirStatus();
    void effectuerMesure(string mesure);
    void creerMission(short, short, string, string);
    void activerModuleEmission();
    void activerInstrument();
    void desactiverInstrument();
    void desactiverModuleEmission();

    void setSegmentSol(SegmentSol* segmentSol) {
        this->segmentSol = segmentSol;
    }
    void configurerRecupEtat(short period, list<string> instrument);
    thread recupEtat();
    thread tLancerMission();
    thread tArretMission();
    thread tSurveillerConstantes();
    Horloge* getHorloge();
    Temperature* getTemperature();
    Instrument* getInstrument();
    Batterie* getBatterie();
    EmetteurRecepteur* getEmetteurRecepteur();
    Mission* getMission();
    Ordinateur* getOrdinateur();
    Etat* getEtat();
    unsigned char getIdentifiant();
    void setIdentifiant(unsigned char id);
    void surveillerConstantes();
    void demandeManuelleReboot();
    char intialisationInstrument();


private:
    unsigned char identifiant;
    Horloge* horloge;
    Temperature* temperature;
    Instrument* instrument;
    Batterie* batterie;
    EmetteurRecepteur* emetteurRecepteur;
    Mission* mission;
    Ordinateur* ordinateur;
    SegmentSol* segmentSol;
    Reboot* reboot;
    Surveillance* surveillance;
    Sauvegarde* sauvegarde;
    Etat* etat;
    bool etatThread;
};

#endif /* SEGMENTVOL_H */

