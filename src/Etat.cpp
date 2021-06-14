/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Etat.cpp
 * Author: snir2g1
 * 
 * Created on 1 avril 2019, 09:50
 */

#include "../defs/Etat.h"

Etat::Etat() {
		periodicity = 3;
}

Etat::~Etat() {
}

short Etat::getPeriodicity(){
    return periodicity;
}

list<string> Etat::getAppareil(){
    return appareil;
}

void Etat::setAppareil(list<string> appareil){
    this->appareil = appareil;
}

void Etat::setPeriodicity(short period){
    periodicity = period;
}
