/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TypeCommande.cpp
 * Author: snir2g2
 * 
 * Created on 19 mars 2019, 15:49
 */

#include "../defs/TypeCommande.h"
#include <string>
using namespace std;

TypeCommande::TypeCommande() {
};

TypeCommande::TypeCommande(const TypeCommande& orig) {
};

TypeCommande::~TypeCommande() {
};

string TypeCommande::MISSION = "MISSION";

string TypeCommande::MEASURE = "MEASURE";

string TypeCommande::STATUS = "STATUS";

string TypeCommande::DEPLOY = "DEPLOY";

string TypeCommande::DATE = "DATE";

string TypeCommande::MEETING = "MEETING";

string TypeCommande::SAVE = "SAVE";

string TypeCommande::SURVIVAL = "SURVIVAL";

string TypeCommande::EMPTY = "EMPTY";





