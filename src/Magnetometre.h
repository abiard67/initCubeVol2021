/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Magnetometre.h
 * Author: LucasG
 *
 * Created on 31 mars 2020, 15:51
 */

#ifndef MAGNETOMETRE_H
#define MAGNETOMETRE_H
#include "../defs/Instrument.h"
#include "../defs/I2C.h"

class Magnetometre : public Instrument, public I2C{
public:
    Magnetometre();
    Magnetometre(const Magnetometre& orig);
    virtual ~Magnetometre();
    bool LireDonnee();
    void activer();
    void desactiver();
    void PassThrough();
	void getChamp(short champ [3]);
    int faireMesure(char arg = -1);
    float* obtenirMesure();
private:
    Mode mode;
    float TempInst;
	short champX;
	short champY;
	short champZ;
    private: short calculerDonnee(char aoctetLow, char aoctetHigh);
    private: float calculerTempInst(char aoctetLow, char aoctetHigh);
protected:
    
        

};

#endif /* MAGNETOMETRE_H */

