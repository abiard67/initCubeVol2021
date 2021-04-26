/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Horloge.cpp
 * Author: snir2g1
 * 
 * Created on 20 mars 2019, 16:10
 */

#include "../defs/Horloge.h"

Horloge::Horloge() {
}

Horloge::~Horloge() {
}

void Horloge::lire() {
    time_t secondes;
    struct tm instant;
    time(&secondes);
    instant = *localtime(&secondes);
    char dh[255] = {};
    int hour, min, sec, year, mon, day;
    char heur[5], minu[5], seco[5], annee[5], mois[5], jour[5];
    dateHeure = "";
    char date[20] = {};
    char heure[20] = {};
    
    hour = instant.tm_hour;
    min = instant.tm_min;
    sec = instant.tm_sec;
    year = instant.tm_year + 1900;
    mon = instant.tm_mon + 1;
    day = instant.tm_mday;
    sprintf(annee,"%d/",year);
    strcat(date,annee);
    
    if(sec < 10){
        sprintf(seco,"0%d",sec);
    } else {
        sprintf(seco,"%d",sec);
    }

    if(min < 10){
        sprintf(minu,"0%d:",min);
    } else {
        sprintf(minu,"%d:",min);
    }

    if(hour < 10){
        sprintf(heur,"0%d:",hour);
    } else {
        sprintf(heur,"%d:",hour);
    }
    strcat(heure,heur);
    strcat(heure,minu);
    strcat(heure,seco);
    
    if(mon < 10){
        sprintf(mois,"0%d/",mon);
    } else {
        sprintf(mois,"%d/",mon);
    }
    strcat(date,mois);
    
    if(day < 10){
        sprintf(jour,"0%d ",day);
    } else {
        sprintf(jour,"%d ",day);
    }
    strcat(date,jour);
    
    strcat(dh, date);
    strcat(dh, heure);
    dateHeure = dh;
}

void Horloge::setRdvTime(string rdvTime) {
    this->rdvTime = rdvTime;
}

string Horloge::getRdvTime() {
    return rdvTime;
}

string Horloge::getDateHeure() {
    return dateHeure;
}

void Horloge::setDateTime(int date, int month, int year,int hour, int min, int sec) {
        //buffer to format command
	unsigned char buff[32]={0};
	//formatting command with the given parameters
	sprintf((char*)buff,(const char *)"date -s \"%02d/%02d/%04d %02d:%02d:%02d\"",month,date,year,hour,min,sec);
	//execute formatted command using system()
	system((const char *)buff);
}

void Horloge::afficherDateTimeLocale(){
        time_t tmm = time(0);
        char* dt = ctime(&tmm);
        cout<< "La date est l'heure locales sont :"<< dt <<endl;
}

void Horloge::afficherDateTimeUTC(){
        time_t tmm = time(0);
        char* dt = ctime(&tmm);
        tm *g = gmtime(&tmm);
        dt = asctime(g);
        cout<< "Horloge UTC :"<< dt <<endl;
}