/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sauvegarde.h
 * Author: Romain
 *
 * Created on 23 juin 2020, 17:42
 */

#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H
//#include "../lib/pugixml-1.9/src/pugixml.hpp"
#include "Mesure.h"

class Sauvegarde {
public:
    Sauvegarde();
    Sauvegarde(const Sauvegarde& orig);
    virtual ~Sauvegarde();
    bool enregistrerMesure(); // initialement prévu : bool enregistrerMesure(Mesure mesure);
    bool ajouterAMission(); // initialement prévu : bool ajouterAMission(Mesure mesure);
    unsigned char lireID();
    Mesure mesure;
};

#endif /* SAUVEGARDE_H */


