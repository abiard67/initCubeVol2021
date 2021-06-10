/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Horloge.h
 * Author: snir2g1
 *
 * Created on 20 mars 2019, 16:10
 */

#ifndef HORLOGE_H
#define HORLOGE_H
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>

using namespace std;

class Horloge {
public:
    Horloge();
    virtual ~Horloge();
    void lire();
    string getRdvTime();
    void setRdvTime(string rdvTime);
    string getDateHeure();
	void initDateTime(int date, int month, int year,int hour, int min, int sec);
private:
    string dateHeure;
    string rdvTime;
};

#endif /* HORLOGE_H */
