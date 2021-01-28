/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SegmentSol.cpp
 * Author: snir2g2
 * 
 * Created on 19 mars 2019, 15:24
 */

#include <iostream>

#include "../defs/SegmentSol.h"
#include "../defs/SegmentVol.h"
#include "../defs/serialib.h"
#include "../defs/Protocole.h"
#include "../defs/Message.h"

                        
using namespace std;
SegmentSol::SegmentSol(SegmentVol *leSegment) {
    this->leSegment=leSegment;
    this->message = new Message();
}


SegmentSol::~SegmentSol() {
}

void SegmentSol::activerReception(){
    
   //int  Ret=LS.Open(DEVICE_PORT,9600);
}

void SegmentSol::envoyerStatus(){

    serialib LS;
	int Ret;
    unsigned char idSegment=leSegment->getIdentifiant();
    message->setIdSegment(idSegment);
	Stockage * leStockage = leSegment->getOrdinateur()->getStockage();
	std::size_t found = leStockage->getUnit().find('k');
	if (found!=std::string::npos) 
	{
		string USDenKilo = leStockage->getMemoireUSD();
		int FUSDenKilo= std::stoi(USDenKilo);
		int FUSDenMo = FUSDenKilo/1024;
		message->setMicroSDenMo(to_string(FUSDenMo));
	}
	else message->setMicroSDenMo(leStockage->getMemoireUSD());
	message->setRAMenPourcent(leStockage->getOccupationRAM());
	message->setTemperatureProc(leSegment->getOrdinateur()->getTemperatureProcessor());
	message->setDateOrdinateur(leSegment->getHorloge()->getDateHeure());
	message->setAmperageBat(leSegment->getBatterie()->getAmperage());
	message->setCapacityBat(leSegment->getBatterie()->getCapacity());
	message->setChargeBat(leSegment->getBatterie()->getChargingLevel());
	message->setChargeStatus(leSegment->getBatterie()->getInCharge());
	message->setTemperatureBat(leSegment->getBatterie()->getTemperature());
	message->setVoltageBat(leSegment->getBatterie()->getVoltage());
	message->setStatInstrument(leSegment->getCameraIR()->getStatus());
	message->setTemperatureCube(leSegment->getTemperature()->getTemperature());
	message->setReboot(leSegment->getOrdinateur()->getReboot());

	int nbrePaquets = 2;
	for (int i=0;i<nbrePaquets;i++)
	{
		Ret=LS.Open(DEVICE_PORT,9600);
		tramerStatus(message, nbrePaquets, i+1);
		Ret=LS.Write(tableau,tableau[2]+6);
		LS.Close();
	}    
}

void SegmentSol::envoyerMission(){
	serialib LS;
	char  Ret;
    unsigned char idSegment=leSegment->getIdentifiant();
    message->setIdSegment(idSegment);
    CameraIR* camera=leSegment->getCameraIR();
    list<Mesure*> mesures=camera->getMesures();
    message->setMesures(mesures);
	Mission * laMission = leSegment->getMission(); 
	string leTypeMission = laMission ->getMeasureType(); 
	message->setTypeMission(leTypeMission);
	int nbrePaquets = this->calculerNombrePaquets(message);
	for (int i=0;i<nbrePaquets;i++)
	{
		Ret=LS.Open(DEVICE_PORT,9600); 

		tramerMission(message, nbrePaquets, i+1);

		Ret=LS.Write(tableau,tableau[2]+6); 

		//auto start = std::chrono::high_resolution_clock::now();
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		//auto end = std::chrono::high_resolution_clock::now();
		// std::chrono::duration<double, std::milli> elapsed = end-start;
		//std::cout << "Waited " << elapsed.count() << " ms\n";
		LS.Close();
	}
	camera->clearMesures();
	mesures=camera->getMesures();

}

void SegmentSol::envoyerMesure(string type){
    serialib LS;
	int Ret;
    unsigned char idSegment=leSegment->getIdentifiant();

    message->setIdSegment(idSegment);

	message->setTypeMesure(type);

	if (type.find(Protocole::TEMPCELSIUS)!= string::npos) {

		list<Mesure*> mesures=leSegment->getCameraIR()->getMesures();
		message->setMesures(mesures);
	}
	else if (type.find(Protocole::PIXEL)!= string::npos) {

		float * mesures= leSegment->getCameraIR()->getPixels();
		for (int i =0;i<64;i++)
		{
			message->addPixel(*(mesures+i));

		}
	}

	int nbrePaquets = 8;
	for (int i=0;i<nbrePaquets;i++)
	{
		Ret=LS.Open(DEVICE_PORT,9600); 
		tramerMesure(message, nbrePaquets, i+1);
		Ret=LS.Write(tableau,tableau[2]+6);
		LS.Close();
	} 
	message->clearPixels();
}



