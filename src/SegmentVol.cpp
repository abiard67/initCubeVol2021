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

#include "../defs/SegmentVol.h"

SegmentVol::SegmentVol() {
    horloge = new Horloge();
    temperature = new Temperature();
    cameraIR = new CameraIR();
    batterie = new Batterie();
    emetteurRecepteur = new EmetteurRecepteur();
    mission = new Mission();
    ordinateur = new Ordinateur();
    etat = new Etat();
    segmentSol = new SegmentSol(this);
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

void SegmentVol::lancerMission() {
    short interval = mission->getPeriodicity();
    etatThread = true;

    while (etatThread) {
        this_thread::sleep_for(chrono::minutes(interval));
        activerInstrument();
        cameraIR->lireTemperature(2);
        horloge->lire();
        cameraIR->setDateMesure(horloge->getDateHeure());
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

void SegmentVol::obtenirStatus(list<string>* appareil) {
    list<string>::iterator it;
    horloge->lire();
    for (it = appareil->begin(); it != appareil->end(); it++) {
        if (*it == TypeAppareil::ORDIBORD) {
            ordinateur->obtenirStatus();
        }
        if (*it == TypeAppareil::INSTRUMENT) {
            cameraIR->obtenirStatus();
        }
        if (*it == TypeAppareil::BATTERIE) {
            batterie->obtenirStatus();
        }
        if (*it == TypeAppareil::CUBE) {
            temperature->recupTempSys();
        }
    }
    activerModuleEmission();
    segmentSol->envoyerStatus();
}

void SegmentVol::obtenirStatus() {
    short intervale = etat->getPeriodicity();
    while (true) {
        this_thread::sleep_for(chrono::minutes(intervale));
        ordinateur->obtenirStatus();
        cameraIR->obtenirStatus();
        batterie->obtenirStatus();
        horloge->lire();
        temperature->recupTempSys();
        activerModuleEmission();
        segmentSol->envoyerStatus();
    }
}

void SegmentVol::effectuerMesure(string mesure) {
    if (mesure == TypeMisEtat::TEMPCELSIUS) {
        activerInstrument();
        cameraIR->lireTemperature(2);
        horloge->lire();
        cameraIR->setDateMesure(horloge->getDateHeure());
        desactiverInstrument();
    } else if (mesure == TypeMisEtat::PIXEL) {
        activerInstrument();
        cameraIR->obtenirPixels();
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

    cameraIR->activer();
}

void SegmentVol::desactiverInstrument() {

    cameraIR->desactiver();
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
    return cameraIR;
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
