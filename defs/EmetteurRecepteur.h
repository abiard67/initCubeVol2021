/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EmmetteurRecepteur.h
 * Author: snir2g1
 *
 * Created on 21 mars 2019, 17:17
 */

#ifndef EMETTEURRECEPTEUR_H
#define EMETTEURRECEPTEUR_H

#include <iostream>

using namespace std;

class EmetteurRecepteur {
public:
    EmetteurRecepteur();
    EmetteurRecepteur(const EmetteurRecepteur& orig);
    virtual ~EmetteurRecepteur();
    void activerEmetteur();
    void desativerEmetteur();
private:

};

#endif /* EMETTEURRECEPTEUR_H */

