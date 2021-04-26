/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Stockage.h
 * Author: Lucas MARYNUS
 *
 * Created on 20 mars 2019, 14:47
 */

#ifndef STOCKAGE_H
#define STOCKAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <string.h>
#include <list>
#include <sstream>
#include <vector>

using namespace std;

class Stockage {
public:
    Stockage();
    virtual ~Stockage();
    
    void calculMemoireUSD();
    void calculMemoireRAM();
    
    string getMemoireRAM();
    string getMemoireUSD();
    string getPourcentage();
    string getOccupationRAM();
    string getUnit();
	void resetStockage();

private:
    
    FILE * ouvrirAccesUSD();
    FILE * ouvrirAccesRAM();

    string lectureLigneUSD(FILE * pFile);
    string lectureLigneRAM(FILE * pFile);
    
    string trouverPositionUSD(string str);
    string trouverPositionRAM(string str);
    
    static string memram;
    static string memUSD;
    
    string memoireRAM;
    string memoireUSD;
    string occupationRAM;
    string pourcentageutilise;
    string unit;
};

#endif /* STOCKAGE_H */
