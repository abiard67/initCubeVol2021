/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Batterie.cpp
 * Author: snir2g1
 * 
 * Created on 14 mars 2019, 16:13
 */

#include "../defs/Batterie.h"

Batterie::Batterie() {
    capacity = 1820;
}

Batterie::~Batterie() {
}

int Batterie::obtenirNiveau() {
    setAddrRegistre(CHARGE_LEVEL_CMD);
    do {
        ecrire();
        char* niveau = lire();
        chargingLevel = niveau[0];
         if (niveau == NULL) {
        return -1;
    }
    } while (chargingLevel < VALEUR_CHARGE_MIN);
}

int Batterie::obtenirCourant() {
    setAddrRegistre(IO_CURRENT_CMD);
    ecrire();
    char* courant = lire();
    amperage = (courant[1] << 8) | courant[0];
    if (amperage & 0x8000) {
        amperage = amperage - 1;
        amperage = ~amperage;
        amperage = -1 * amperage;
    }
    else 
        return -1 ;
}

int Batterie::obtenirTemperature() {
    setAddrRegistre(BATTERY_TEMPERATURE_CMD);
    ecrire();
    char* temp = lire();
    temperature = (temp[1] << 8) | temp[0];
    if (temp == NULL) {
        return -1;
    }
}

int Batterie::obtenirCharge() {
    setAddrRegistre(STATUS_CMD);
    ecrire();
    char* stat = lire();
    short statu = (stat[0] >> 2) & 0x03;
    if ((statu == 1) || (statu == 2)) {
        inCharge = true;
    } else {
        inCharge = false;
    }
	return 0;
}

int Batterie::obtenirTension() {
    setAddrRegistre(BATTERY_VOLTAGE_CMD);
    ecrire();
    char* tension = lire();
    voltage = ((tension[1] << 8) | tension[0]) / 1000.0;
    if (tension == NULL) {
        return -1;
    }
}

int Batterie::obtenirStatus() {
    setAddrEsclave(0x14);

    obtenirNiveau();
    obtenirCourant();
    obtenirTemperature();
    obtenirCharge();
    obtenirTension();
    return 0;
}
void Batterie::resetStatus()
{
	chargingLevel = 0;
    voltage = 0;
    amperage = 0;
    inCharge = false;
    temperature = 0;
}

unsigned char Batterie::getChargingLevel() {
    return chargingLevel;
}

float Batterie::getVoltage() {
    return voltage;
}

short Batterie::getAmperage() {
    return amperage;
}

bool Batterie::getInCharge() {
    return inCharge;
}

float Batterie::getTemperature() {
    return temperature;
}

short Batterie::getCapacity() {
    return capacity;
}
