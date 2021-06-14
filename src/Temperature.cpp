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

char Temperature::positif = 1;
char Temperature::negatif = 2;

Temperature::Temperature() {
	temperaturesys=0;
}

Temperature::Temperature(const Temperature& orig) {
}

Temperature::~Temperature() {
}

int Temperature::recupTempSys() {
    float temperatureHigh, temperatureLow;
    setAddrEsclave(adressecapteuri2c);
    setAddrRegistre(pointeurderegistre);
    ecrire();
    char* valeurLue = lire();
    temperatureHigh = valeurLue[0] & bithuitadouze;
    temperatureLow = valeurLue[1];
    if ((valeurLue[0] & bitdesigne) == bitdesigne) {

        //TEMPERATURE N�GATIVE
        temperaturesys = (float) (256.0 - ((temperatureHigh * 16.0) + (temperatureLow / 16.0)));
        temperaturesys = -1 * temperaturesys;
		return negatif;
    } else {

        //TEMPERATURE POSITIVE
        temperaturesys = (float) (temperatureHigh * 16.0 + temperatureLow / 16.0);
		return positif;
    }
	return 0;
}

void Temperature::resetTemperature()
{
	temperaturesys=0;
}

float Temperature::getTemperature() {
    return this->temperaturesys;
}
