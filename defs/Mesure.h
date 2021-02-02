/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mesure.h
 * Author: snir2g2
 *
 * Created on 14 mars 2019, 17:40
 */

#ifndef MESURE_H
#define MESURE_H

#include <string>
#include <iostream>

using namespace std;

class Mesure {
public:
    Mesure();
    Mesure(float valeur);
    virtual ~Mesure();
    void setDateHour(string dateHour);
    string getUnite();
    float getMesure();
    string getDateHour();
private:
    float value;
    string dateHour;
    string unit;

};

#endif /* MESURE_H */

