/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Etat.h
 * Author: snir2g1
 *
 * Created on 1 avril 2019, 09:50
 */

#ifndef ETAT_H
#define ETAT_H
#include <string>
#include <list>

using namespace std;

class Etat {
public:
    Etat();
    virtual ~Etat();
    short getPeriodicity();
    list<string> getAppareil();
    void setPeriodicity(short period);
    void setAppareil(list<string> appareil);
private:
    short periodicity;
    list<string> appareil;
};

#endif /* ETAT_H */

