/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Surveillance.h
 * Author: Romain
 *
 * Created on 23 juin 2020, 17:41
 */

#ifndef SURVEILLANCE_H
#define SURVEILLANCE_H

#include "Ordinateur.h"
#include "Batterie.h"
#include "Stockage.h"
#include "Sauvegarde.h"
#include "Horloge.h"

#define tempProcessAcceptable 40 // 70 OU 85 MAIS 40 POUR TEST
#define tempBattAcceptable 45 // OU 59

class Surveillance {
public:
    Surveillance();
    Surveillance(const Surveillance& orig);
    virtual ~Surveillance();
    void surveillerConstantes();
    void demandeReboot();
    void valeurIncompatible();
private:
    bool etatThread;
    Sauvegarde* sauvegarde;
    Reboot* reboot;
    Ordinateur* ordinateur;
    Batterie* batterie;
    Stockage* stockage;
    Horloge* horloge;
};

#endif /* SURVEILLANCE_H */