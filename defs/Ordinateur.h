/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ordinateur.h
 * Author: Lucas MARYNUS
 *
 * Created on 20 mars 2019, 14:47
 */

#ifndef ORDINATEUR_H
#define ORDINATEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <list>
#include <sstream>
#include <vector>

#include "../defs/Stockage.h"
#include "../defs/Reboot.h"

using namespace std;

class Ordinateur {
public:
    Ordinateur();
    virtual ~Ordinateur();
    int obtenirStatus();
    bool resetStatus();        
    Stockage * getStockage();
    float getTemperatureProcessor();
	Reboot* getReboot();


protected:
    
private:
    Stockage* leStockage;
	Reboot* leReboot;
    float temperatureProcessor;
    void calculerStockage();
    int obtenirTemperature();
};

#endif /* ORDINATEUR_H */
