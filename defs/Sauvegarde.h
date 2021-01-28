/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sauvegarde.h
 * Author: snir2g2
 *
 * Created on 25 mars 2019, 09:01
 */

#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include "Mesure.h"

class Sauvegarde {
public:
    Sauvegarde();
    Sauvegarde(const Sauvegarde& orig);
    virtual ~Sauvegarde();
    bool enregitrerMesure(Mesure mesure);
private:

};

#endif /* SAUVEGARDE_H */

