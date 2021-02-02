/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Batterie.h
 * Author: snir2g1
 *
 * Created on 14 mars 2019, 16:13
 */

#ifndef BATTERIE_H
#define BATTERIE_H
#include "I2C.h"

#define   STATUS_CMD            0x40
#define   CHARGE_LEVEL_CMD      0x41
#define   BATTERY_TEMPERATURE_CMD       0x47 
#define   BATTERY_VOLTAGE_CMD   0x49 
#define   BATTERY_CURRENT_CMD   0x4b 
#define   IO_VOLTAGE_CMD        0x4d 
#define   IO_CURRENT_CMD        0x4f
#define   VALEUR_CHARGE_MIN     20


class Batterie : public I2C {
public:
    Batterie();
    virtual ~Batterie();
    void obtenirStatus();
    unsigned char getChargingLevel();
    float getVoltage();
    short getAmperage();
    bool getInCharge();
    float getTemperature();
    short getCapacity();
private:
    unsigned char chargingLevel;
    float voltage;
    short amperage;
    bool inCharge;
    float temperature;
    short capacity;
    void obtenirNiveau();
    void obtenirCourant();
    void obtenirTemperature();
    void obtenirCharge();
    void obtenirTension();
};

#endif /* BATTERIE_H */

