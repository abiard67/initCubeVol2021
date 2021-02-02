/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Stockage.cpp
 * Author: Lucas MARYNUS
 * 
 * Created on 20 mars 2019, 14:47
 */
#include <sstream>
#include "../defs/Stockage.h"
#include "../defs/Ordinateur.h"


string  Stockage::memram = "Mem:";
string  Stockage::memUSD = "/dev/root";

Stockage::Stockage(){
    memoireRAM = "666666";
    memoireUSD = "1888888";
    pourcentageutilise = "66";
	occupationRAM="77";
	unit="ko";
}

Stockage::~Stockage() {
}


FILE * Stockage::ouvrirAccesUSD(){
    FILE * fichierUSD = popen("df -k", "r");
    return fichierUSD;
}

string Stockage::lectureLigneUSD(FILE * pFile){
    char bufferUSD[500];
    string newstringUSD;
    do{
        fscanf(pFile, "%400c", bufferUSD);
        newstringUSD = std::string(bufferUSD);
    }while(newstringUSD.find(memUSD) == std::string::npos);
    return newstringUSD;
}

string Stockage::trouverPositionUSD(string str){
    size_t posUSD;
    
    posUSD = str.find(memUSD);
    string memoirefreeUSD = str.substr(posUSD,150);
    return memoirefreeUSD;
}

void Stockage::calculMemoireUSD(){
    FILE * fichierU = ouvrirAccesUSD();
    string ligneU = lectureLigneUSD(fichierU);
    string memoirelibreUSD = trouverPositionUSD(ligneU);           
    int ndestringe = 0;
    string strUSD;
    
    istringstream issUSD(memoirelibreUSD);
    while(getline(issUSD, strUSD, ' '))
        
    if (strUSD!=""){
        if (ndestringe==3) memoireUSD=strUSD;
        if (ndestringe==4) pourcentageutilise=strUSD.substr(0, strUSD.size()-1);
        ndestringe = ndestringe+1;
    }
   
} 

string Stockage::getMemoireUSD(){
    return memoireUSD;    
}

string Stockage::getPourcentage(){
    return pourcentageutilise;
}

string Stockage::getUnit(){
    return unit;
}


//----------------------------------------------------//




FILE * Stockage::ouvrirAccesRAM(){
    FILE * fichierRAM = popen("free -t", "r");
    //if(fichierRAM < 0){
    //    cout << "Erreur de fichier RAM" << endl;
    //}
    return fichierRAM;
}

string Stockage::lectureLigneRAM(FILE * pFile){
    char bufferRAM[500];
    string newstringRAM;
    
    do{
        fscanf(pFile, "%200c", bufferRAM);
        newstringRAM = std::string(bufferRAM); 
    }while(newstringRAM.find(memram) == std::string::npos);
    return newstringRAM;
}

string Stockage::trouverPositionRAM(string str){
    size_t posRAM;
    string memoirefreeRAM;
    posRAM = str.find(memram);
    memoirefreeRAM = str.substr(posRAM,80);
    return memoirefreeRAM;
}

void Stockage::calculMemoireRAM(){
    FILE * fichierR = ouvrirAccesRAM();
    string ligneR = lectureLigneRAM(fichierR);
    string memoirelibreRAM = trouverPositionRAM(ligneR);
    
    int ndestring = 0;
    string strRAM;
    string occupRAM;
    string memoireRAMtotale;
    
    float fmemoireRAMtotale;
    float foccupRAM;
    
  
    istringstream issRAM (memoirelibreRAM);
    while(getline(issRAM, strRAM, ' '))
    if (strRAM != ""){
        if(ndestring == 1)  memoireRAMtotale= strRAM;
        if(ndestring == 2)  occupRAM=strRAM;
        if(ndestring == 3)  memoireRAM=strRAM;
        ndestring += 1;
    }
    
    ostringstream occupacionRam;
    fmemoireRAMtotale = strtof(memoireRAMtotale.c_str(), 0);
    foccupRAM = strtof(occupRAM.c_str(), 0);
    occupacionRam << (int)(((foccupRAM) / (fmemoireRAMtotale)) * 100); //Pas de pourcent dans la valeur...
    this->occupationRAM= string(occupacionRam.str());

}



string Stockage::getMemoireRAM(){
    return memoireRAM;
}

string Stockage::getOccupationRAM(){
    return occupationRAM;
}