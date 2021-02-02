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

Surveillance::Surveillance() {
}

Surveillance::Surveillance(const Surveillance& orig) {
}

Surveillance::~Surveillance() {
}

void Surveillance::surveillerConstantes() {
    etatThread = true;
    while (etatThread) {
        sleep(1);
        if (ordinateur->getTemperatureProcessor() > tempProcessAcceptable) {
            valeurIncompatible();
        } else if (batterie->getTemperature() > tempBattAcceptable) {
            valeurIncompatible();
        } else if (stockage->getOccupationRAM() > stockage->getMemoireRAM()) {
            valeurIncompatible();
        }
    }
}

void Surveillance::valeurIncompatible() {
    etatThread = false;
    sauvegarde->enregistrerMesure();
    reboot->setNumber(reboot->getNumber()+1);
    reboot->setDateHour(horloge->getDateHeure());
    reboot->systemeReboot();
}