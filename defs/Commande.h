/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Commande.h
 * Author: snir2g2
 *
 * Created on 19 mars 2019, 15:35
 */

#ifndef COMMANDE_H
#define COMMANDE_H

#include <list>
#include "TypeCommande.h"

class Commande {
public:
    Commande();
    virtual ~Commande();
    void setCode(string cmd);
    string getCode();
private:
    string code;
    list<string> parametres;
};

#endif /* COMMANDE_H */

