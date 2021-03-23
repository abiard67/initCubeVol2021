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
    
  
    while (true) {

        mutex_serial.lock();

        serialib * monObjSerial = new serialib; //Déclaration de l'instance
        Protocole* ObjRetourAck = new Protocole();
        monObjSerial->Open("/dev/serial0", 9600); //Ouverture 



        char trame[104];
        char varID = leSegment->getIdentifiant();



        int typeRetourTrame = monObjSerial->ReadString(trame, '\n', 128, 3000);
        cout << "Valeur de Retour : " << typeRetourTrame << endl;

        if (typeRetourTrame == 0) {
            cout << "Pas de commande reçu." << endl;
            monObjSerial->Close();
            mutex_serial.unlock();
        } else if (typeRetourTrame == -1) {
            cout << "Erreur TimeOut mal définie" << endl;
            ObjRetourAck->envoieACK("ERROR");
            monObjSerial->Close();
            mutex_serial.unlock();
        } else if (typeRetourTrame == -2) {
            cout << "Erreur impossible d'accéder à la ressource." << endl;
            ObjRetourAck->envoieACK("ERROR");
            monObjSerial->Close();
            mutex_serial.unlock();
        } else if (typeRetourTrame == -3) {
            cout << "Erreur, trop d'octects lus." << endl;
            ObjRetourAck->envoieACK("BUSY");
            monObjSerial->Close();
            mutex_serial.unlock();
        } else if (typeRetourTrame > 1) {
            cout << "Reception de la Commande OK " << endl;

            cout << "Trame Lue : ";
            for (int i(0); i < typeRetourTrame; i++) {
                cout << trame[i];
            }
            if (trame[1] == varID) {
                cout << "La commande est pour notre Cube" << endl;
                //ObjRetourAck->envoieACK("OK");
                
                bool boolChecksum = this->verifierChecksum();
                if (boolChecksum == true) {
                    ObjRetourAck->envoieACK("ACK");
                }
                if (boolChecksum == false) {
                    ObjRetourAck->envoieACK("NACK");
                }


            } else {
                cout << "La commande n'est pas pour notre Cube" << endl;
            }
            monObjSerial->Close();
            mutex_serial.unlock();
        } else {
            monObjSerial->Close();
            mutex_serial.unlock();
        }
    }
}

thread SegmentSol::tActiverReception() {
    return thread([this] {
        activerReception();
    });
}


void SegmentSol::testEnvoie() {

    mutex_serial.lock();
    char monChar = '7';

    //Ouverture de l'accès à la ressource
    serialib * monObjSerialTest = new serialib;
    int typeRetourAccesRessource = monObjSerialTest->Open("/dev/serial0", 9600);

    if (typeRetourAccesRessource == 1) {
        cout << "Accès à la ressource pour un test d'envoie : réussi" << endl;
    } else {
        cout << "Accès à la ressource pour un test d'envoie : échoué" << endl;
    }

    //Ecriture du Test d'envoie vers le port serial
    int typeRetourTestEnvoie = monObjSerialTest->WriteChar(monChar);

    if (typeRetourTestEnvoie >= 1) {
        cout << "Ecriture vers la ressource pour un test d'envoie : réussi" << endl;
    } else {
        cout << "Ecriture vers la ressource pour un test d'envoie : échoué" << endl;
    }

    monObjSerialTest->Close();
    mutex_serial.unlock();

}

thread SegmentSol::tTestEnvoie() {
    return thread([this] {
        testEnvoie();
    });
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
		//Ret=LS.Open(DEVICE_PORT,9600);
		tramerStatus(message, nbrePaquets, i+1);
		//Ret=LS.Write(tableau,tableau[2]+6);
		//LS.Close();
		cout<<"Envoi status"<< tableau<<endl;
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
		//Ret=LS.Open(DEVICE_PORT,9600); 

		//tramerMission(message, nbrePaquets, i+1);

		Ret=LS.Write(tableau,tableau[2]+6); 

						//auto start = std::chrono::high_resolution_clock::now();
						//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						//auto end = std::chrono::high_resolution_clock::now();
						// std::chrono::duration<double, std::milli> elapsed = end-start;
						//std::cout << "Waited " << elapsed.count() << " ms\n";
		//LS.Close();
				cout<<"Envoi status"<< tableau<<endl;
	}
	camera->clearMesures();
	mesures=camera->getMesures();

}

void SegmentSol::traiterCommande(){
    
}

thread SegmentSol::tTraiterCommande() {
    return thread([this] {
        traiterCommande();
    });
}

void SegmentSol::envoyerMesure(string type){
    serialib LS;
	int Ret;
	CameraIR* camera=leSegment->getCameraIR();
    unsigned char idSegment=leSegment->getIdentifiant();

    message->setIdSegment(idSegment);

	message->setTypeMesure(type);

	if (type.find(Protocole::TEMPCELSIUS)!= string::npos) {

		list<Mesure*> mesures=leSegment->getCameraIR()->getMesures();
		message->setMesures(mesures);
		int nbrePaquets = 1;
		for (int i=0;i<nbrePaquets;i++)
		{
			//Ret=LS.Open(DEVICE_PORT,9600); 
			tramerMesure(message, nbrePaquets, 1);
			//Ret=LS.Write(tableau,tableau[2]+6);
			//LS.Close();
					cout<<"Envoi mesure TC"<< tableau<<endl;
		} 
		message->clearMesures();
		camera->clearLastMesures();
	}
	else if (type.find(Protocole::PIXEL)!= string::npos) {

		float * mesures= leSegment->getCameraIR()->getPixels();
		for (int i =0;i<64;i++)
		{
			message->addPixel(*(mesures+i));
			cout<<"prel  PIXELS"<< *(mesures+i)<<endl;

		}
		int nbrePaquets = 8;
		for (int i=0;i<nbrePaquets;i++)
		{
			//Ret=LS.Open(DEVICE_PORT,9600); 
			tramerMesure(message, nbrePaquets, i+1);
			//Ret=LS.Write(tableau,tableau[2]+6);
			//LS.Close();
					cout<<"Envoi mesure PIXELS"<< tableau<<endl;
		} 
		message->clearPixels();
	}


}



