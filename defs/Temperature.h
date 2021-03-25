/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Temperature.h
 * Author: Lucas MARYNUS
 *
 * Created on 14 mars 2019, 15:08
 */

#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <math.h>
#include <iostream>

#include "../defs/I2C.h"

using namespace std;

class Temperature : public I2C {
public:
    Temperature();
    Temperature(const Temperature& orig);
    virtual ~Temperature();
    int recupTempSys();
    float getTemperature();
    void sePlacer();
    
private:
    static char bitdesigne;
    static char adressecapteuri2c;
    static char pointeurderegistre;
    static char bithuitadouze;
    float temperaturesys;
};

#endif /* TEMPERATURE_H */
