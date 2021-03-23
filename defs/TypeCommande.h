/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TypeCommande.h
 * Author: snir2g2
 *
 * Created on 19 mars 2019, 15:49
 */

#ifndef TYPECOMMANDE_H
#define TYPECOMMANDE_H
#include "string"

using namespace std;
class TypeCommande {
public:
    TypeCommande();
    TypeCommande(const TypeCommande& orig);
    virtual ~TypeCommande();
private:
protected:
    static string MISSION;
    static string MEASURE;
    static string STATUS;
    static string DEPLOY;
    static string DATE;
    static string MEETING;
    static string SAVE;
    static string SURVIVAL;
    static string EMPTY;
};

#endif /* TYPECOMMANDE_H */

