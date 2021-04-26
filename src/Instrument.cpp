/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InstrumentPhantom.cpp
 * Author: snir2g2
 * 
 * Created on 27 mars 2019, 13:19
 */

#include "../defs/Instrument.h"
#include <iostream>
#include <string>

using namespace std;

Instrument::Instrument() {
    status = new Status();
}

Instrument::Instrument(const Instrument& orig) {
}

Instrument::~Instrument() {
}

list<Mesure*> Instrument::getMesures() {
    return listedemesures;
}
;
void Instrument::clearMesures() {
	this->listedemesures.clear();
}

void Instrument::clearLastMesures() {
	this->listedemesures.pop_back();
}

int Instrument::obtenirStatus() {
    obtenirMode();
    obtenirTempInst();
    return 0;
}

void Instrument::resetStatus()
{
	status->setMode(SLEEP);
	status->setOnOff(false);
	status->setTemp(0);
}

Status * Instrument::getStatus() {
    return status;
}

void Instrument::addMesure(Mesure * auneMesure) {
	listedemesures.push_back(auneMesure);
}

void Instrument::setDateMesure(string adateHour) {
	listedemesures.back()->setDateHour(adateHour);
}

