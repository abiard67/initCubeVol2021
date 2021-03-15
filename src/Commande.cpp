/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Commande.cpp
 * Author: snir2g2
 * 
 * Created on 19 mars 2019, 15:35
 */

#include "../defs/Commande.h"
#include<list>
Commande::Commande() {
}

Commande::~Commande() {
}

string Commande::getCode(){
    
    return code;
}

void Commande::setCode(string cmd){
    
    this->code = cmd;
}

void Commande::setParametres(list<string> parametres){
    this->parametres = parametres;
}

std::list<string> Commande::getParametres(){

    return parametres;
}