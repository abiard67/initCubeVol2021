/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Message.h
 * Author: snir2g2
 *
 * Created on 19 mars 2019, 15:37
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <list>
#include "../defs/Mesure.h"
#include "../defs/Status.h"
#include "../defs/Reboot.h"

  using namespace std;

class Message {
public:
    Message();
    Message(const Message& orig);
    virtual ~Message();

	unsigned char getIdSegment();
	list<Mesure*> getMesures();
	string getTypeMission();
	string getMicroSDenMo();
	string getRAMenPourcent();

	string getDateOrdinateur();
	string getTemperatureProc();
	string getChargeBat();
	string getAmperageBat();
	bool getChargeStatus();
	string getTemperatureBat();
	string getVoltageBat();
	string getCapacityBat();
	Status * getStatInstrument();
	string getTemperatureCube();
	Reboot* getReboot();
	 ////////// Modification depuis la dernière fois pour récupérer cette information
	string getTypeMesure();
    list<string> getPixels();


    void setIdSegment(unsigned char id);
    void setMesures(list<Mesure*> mesures);
	void setTypeMission(string typeMission); 
	void setMicroSDenMo(string amicroSDenMo);
	void setRAMenPourcent(string aRAMenPourcent);
	void setTemperatureProc(float atemperatureProc);
	void setDateOrdinateur(string adateOrdinateur);
	void setChargeBat(char achargeBat);
	void setAmperageBat(short aamperageBat);
	void setChargeStatus(bool achargeStatus);
	void setTemperatureBat(float atemperatureBat);
	void setVoltageBat(float avoltageBat);
	void setCapacityBat(short acapacityBat);
	void setStatInstrument(Status * astatInstrument);
	void setTemperatureCube(float atemperatureCube);
	void setReboot(Reboot* areboot);
	////////// Modification depuis la dernière fois pour modifier cette information
	void setTypeMesure(string type);
	void addPixel(float leReleve);
	void clearPixels();
	void setPixels(list<string> lesNouveauxPixels);


private:
    unsigned char idSegment;
    list<Mesure*> mesures;
	string typeMission;

	string microSDenMo;
	string RAMenPourcent;
	string temperatureProc;
	string dateOrdinateur;
	string chargeBat;
	string voltageBat;
	string amperageBat;
	bool chargeStatus;
	string temperatureBat;
	string capacityBat;
	Status * statInstrument;
	/**
	 * Cet attribut correspond à la température du cube, entre les cartes.
	 */
	string temperatureCube;
	Reboot* reboot;  
	////////// Modification depuis la dernière fois pour récupérer cette information
	string typeMesure;
	list<string> pixels;
};

#endif /* MESSAGE_H */



