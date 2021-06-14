/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ordinateur.cpp
 * Author: Lucas MARYNUS
 * 
 * Created on 20 mars 2019, 14:47
 */

#include <vector>
#include <iostream>
#include "../defs/Stockage.h"
#include "../defs/Ordinateur.h"

Ordinateur::Ordinateur() {
    leStockage = new Stockage();
	leReboot = new Reboot();
}

Ordinateur::~Ordinateur() {
}

void Ordinateur::calculerStockage(){
    leStockage->calculMemoireUSD();
    leStockage->calculMemoireRAM();
}

int Ordinateur::obtenirStatus(){
    calculerStockage();
    obtenirTemperature();
    return 0;
}

bool Ordinateur::resetStatus()
{
	leStockage->resetStockage();
	temperatureProcessor=0;
	return true;
}

float Ordinateur::getTemperatureProcessor(){
    return this->temperatureProcessor;
}

Stockage * Ordinateur::getStockage(){
    return this->leStockage;
}

Reboot* Ordinateur::getReboot() {
	return leReboot;
}

int Ordinateur::obtenirTemperature(){
    FILE *temperatureFile;
    double temp;
    temperatureFile = fopen ("/sys/class/thermal/thermal_zone0/temp", "r");
    if (temperatureFile == NULL){
       // perror("temp");
        return -1 ;
    } else {
        fscanf (temperatureFile, "%lf", &temp);
        temperatureProcessor=temp / 1000;
        fclose (temperatureFile);
        return 0;
    }
}