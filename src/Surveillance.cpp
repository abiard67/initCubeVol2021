/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Surveillance.cpp
 * Author: Romain
 * 
 * Created on 23 juin 2020, 17:41
 */

#include "../defs/Surveillance.h"

Surveillance::Surveillance(SegmentVol* segmentVol) {
	this->segmentVol=segmentVol;
	sauvegarde = new Sauvegarde();
}

Surveillance::Surveillance(const Surveillance& orig) {
}

Surveillance::~Surveillance() {
}

void Surveillance::surveillerConstantes() {
    etatThread = true;
    while (etatThread) {
        sleep(1);
		if (segmentVol->getOrdinateur()->getTemperatureProcessor() > tempProcessAcceptable) {
            valeurIncompatible();
		} else if (segmentVol->getBatterie()->getTemperature() > tempBattAcceptable) {
            valeurIncompatible();
		} else if (segmentVol->getOrdinateur()->getStockage()->getOccupationRAM() > segmentVol->getOrdinateur()->getStockage()->getMemoireRAM()) {
            valeurIncompatible();
        }
    }
}

void Surveillance::valeurIncompatible() {
    etatThread = false;
	sauvegarde->enregistrerMesures(segmentVol->getInstrument()->getMesures());
	segmentVol->getOrdinateur()->getReboot()->setNumber(segmentVol->getOrdinateur()->getReboot()->getNumber()+1);
	segmentVol->getOrdinateur()->getReboot()->setDateHour(segmentVol->getHorloge()->getDateHeure());
    segmentVol->getOrdinateur()->getReboot()->systemeReboot();
}