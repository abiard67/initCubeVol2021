/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Temperature.cpp
 * Author: Lucas MARYNUS
 * 
 * Created on 14 mars 2019, 15:08
 */

#include "../defs/Temperature.h"
#include "../defs/I2C.h"

char Temperature::bitdesigne = 0x10;
char Temperature::bithuitadouze = 0x1F;

char Temperature::adressecapteuri2c = 0x18;
char Temperature::pointeurderegistre = 0x05;

Temperature::Temperature() {
}

Temperature::Temperature(const Temperature& orig) {
}

Temperature::~Temperature() {
}

void Temperature::recupTempSys() {
    float temperatureHigh, temperatureLow;
    setAddrEsclave(adressecapteuri2c);
    setAddrRegistre(pointeurderegistre);
    ecrire();
    char* valeurLue = lire();
    temperatureHigh = 12; //valeurLue[0] & bithuitadouze;
    temperatureLow = 86; //valeurLue[1];
    if ((valeurLue[0] & bitdesigne) == bitdesigne) {

        //TEMPERATURE N�GATIVE
        temperaturesys = (float) (256.0 - ((temperatureHigh * 16.0) + (temperatureLow / 16.0)));
        temperaturesys = -1 * temperaturesys;
    } else {

        //TEMPERATURE POSITIVE
        temperaturesys = (float) (temperatureHigh * 16.0 + temperatureLow / 16.0);

    }
}

float Temperature::getTemperature() {
    return this->temperaturesys;
}
