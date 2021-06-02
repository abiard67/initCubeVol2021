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
#include "../defs/FrameManager.h"
#include "../defs/Message.h"


using namespace std;

    mutex mutex_serial, mutex_message;
	condition_variable cv;
	bool ready = false;

SegmentSol::SegmentSol(SegmentVol *leSegment) {
    this->leSegment = leSegment;

}

SegmentSol::~SegmentSol() {
}

void SegmentSol::activerReception() {
	serialib * monObjSerial = new serialib; //Déclaration de l'instance
	vector<char> laTrame;
	vector<char>::iterator it ;
    while (true) {

		unique_lock<mutex> lck(mutex_serial);
		while (ready) 	cv.wait(lck);
        monObjSerial->Open("/dev/serial0", 9600); //Ouverture
        char varID = leSegment->getIdentifiant();
		message->setIdSegment(varID);
        int typeRetourTrame = monObjSerial->ReadString(trameReception, 255, 128, 100);

		if (typeRetourTrame == -3) {
			laTrame = this->tramerRepAcq(message,"BUSY");

			for (it = laTrame.begin(); it != laTrame.end() ; it++) {
				monObjSerial->WriteChar(*it);
			}
        } else if (typeRetourTrame > 1) {
          cout << "Trame reçue" << endl;
                if (trameReception[0] == varID)
				{
                    cout << "Trame pour notre Sat" << endl;
                    bool boolChecksum = this->verifierChecksum();
                    if (boolChecksum == true) {
                    cout << "Envoie de l'ACK" << endl;
						laTrame = this->tramerRepAcq(message,"ACK");


						for (it = laTrame.begin(); it != laTrame.end() ; it++) {
							monObjSerial->WriteChar(*it);
						}
                        cout << "Ajout d'une commande reçue à la fille d'attente..." << endl;
                        this->ajouter_cmd_queue(trameReception);
                    }
					else {
            cout << "Envoie d'un NACK" << endl;
            laTrame = this->tramerRepAcq(message,"NACK");


						for (it = laTrame.begin(); it != laTrame.end() ; it++) {
							monObjSerial->WriteChar(*it);
						}
                    }
                }
        }
    //Pas de commande reçue
		monObjSerial->Close();
    }
}





thread SegmentSol::tActiverReception() {
    return thread([this] {
        activerReception();
    });
}

void SegmentSol::envoyerStatus(list<string> status) {

    serialib LS;
    int Ret;
	bool argumentsOK=true;
    list<string>::iterator it;
	int nbrePaquets = 0;
    unsigned char idSegment = leSegment->getIdentifiant();
    message->setIdSegment(idSegment);
    if (status.begin() == status.end()) {
        //ORDIBORD
        Stockage * leStockage = leSegment->getOrdinateur()->getStockage();
        std::size_t found = leStockage->getUnit().find('k');
        if (found != std::string::npos) {
            string USDenKilo = leStockage->getMemoireUSD();
            int FUSDenKilo = std::stoi(USDenKilo);
            int FUSDenMo = FUSDenKilo / 1024;
            message->setMicroSDenMo(to_string(FUSDenMo));
        }
        message->setTemperatureProc(leSegment->getOrdinateur()->getTemperatureProcessor());
        message->setMicroSDenMo(leStockage->getMemoireUSD());
        message->setRAMenPourcent(leStockage->getOccupationRAM());
        message->setDateOrdinateur(leSegment->getHorloge()->getDateHeure());
		//REBOOT
        message->setReboot(leSegment->getOrdinateur()->getReboot());
        //BATTERIE
        message->setAmperageBat(leSegment->getBatterie()->getAmperage());
        message->setCapacityBat(leSegment->getBatterie()->getCapacity());
        message->setChargeBat(leSegment->getBatterie()->getChargingLevel());
        message->setChargeStatus(leSegment->getBatterie()->getInCharge());
        message->setTemperatureBat(leSegment->getBatterie()->getTemperature());
        message->setVoltageBat(leSegment->getBatterie()->getVoltage());
        //INSTRUMENT
        message->setStatInstrument(leSegment->getInstrument()->getStatus());
        //CUBE
        message->setTemperatureCube(leSegment->getTemperature()->getTemperature());
		nbrePaquets = 2;

    } else for (it = status.begin(); it != status.end(); it++) {

            //ordinateur
            if (*it == TypeAppareil::ORDIBORD) {
                Stockage * leStockage = leSegment->getOrdinateur()->getStockage();
                std::size_t found = leStockage->getUnit().find('k');
                if (found != std::string::npos) {
                    string USDenKilo = leStockage->getMemoireUSD();
                    int FUSDenKilo = std::stoi(USDenKilo);
                    int FUSDenMo = FUSDenKilo / 1024;
                    message->setMicroSDenMo(to_string(FUSDenMo));
                }
                message->setTemperatureProc(leSegment->getOrdinateur()->getTemperatureProcessor());
                message->setMicroSDenMo(leStockage->getMemoireUSD());
                message->setRAMenPourcent(leStockage->getOccupationRAM());
                message->setDateOrdinateur(leSegment->getHorloge()->getDateHeure());
				nbrePaquets++;

            }//BATT
            else if (*it == TypeAppareil::BATTERIE) {
                message->setAmperageBat(leSegment->getBatterie()->getAmperage());
                message->setCapacityBat(leSegment->getBatterie()->getCapacity());
                message->setChargeBat(leSegment->getBatterie()->getChargingLevel());
                message->setChargeStatus(leSegment->getBatterie()->getInCharge());
                message->setTemperatureBat(leSegment->getBatterie()->getTemperature());
                message->setVoltageBat(leSegment->getBatterie()->getVoltage());
				nbrePaquets++;
            }//Instrument
            else if (*it == TypeAppareil::INSTRUMENT) {
                message->setStatInstrument(leSegment->getInstrument()->getStatus());
				nbrePaquets++;
            }//Cube
            else if (*it == TypeAppareil::CUBE) {
                message->setTemperatureCube(leSegment->getTemperature()->getTemperature());
				nbrePaquets++;
            }
			else if (*it == TypeAppareil::REBOOT) {
				message->setReboot(leSegment->getOrdinateur()->getReboot());
				if (message->getTemperatureCube() =="0") nbrePaquets++;
            }
			else {
				argumentsOK=false;
			}
        }

		ready = true;
		unique_lock<mutex> lck(mutex_serial);
		if (argumentsOK)
		{
			for (int i = 0; i < nbrePaquets; i++) {
			Ret = LS.Open(DEVICE_PORT, 9600);
			if (Ret >= 1) {

				tramerStatus(message, status, nbrePaquets, i + 1);
				Ret = LS.Write(trameEmission, trameEmission[1] + 5);
				LS.Close();
				}
			}
		}
		else {
				vector<char> laTrame = this->tramerRepAcq(message,"ERROR-E13");
				vector<char>::iterator it ;
				Ret = LS.Open(DEVICE_PORT, 9600);
				for (it = laTrame.begin(); it != laTrame.end() ; it++) {
					LS.WriteChar(*it);
				}
				LS.Close();

		}
    cv.notify_all();
    ready = false;
	message=new Message();
}

void SegmentSol::envoyerMission() {
    serialib LS;
    char Ret;
    unsigned char idSegment = leSegment->getIdentifiant();
    message->setIdSegment(idSegment);
    Instrument* instrument = leSegment->getInstrument();
    list<Mesure*> mesures = instrument->getMesures();
    message->setMesures(mesures);
    Mission * laMission = leSegment->getMission();
    string leTypeMission = laMission ->getMeasureType();
    message->setTypeMission(leTypeMission);
    int nbrePaquets = this->calculerNombrePaquets(message);
	ready = true;
	std::unique_lock<std::mutex> lck(mutex_serial);

    for (int i = 0; i < nbrePaquets; i++) {
        Ret=LS.Open(DEVICE_PORT,9600);
        tramerMission(message, nbrePaquets, i+1);
        Ret = LS.Write(trameEmission, trameEmission[1] + 5);

        //auto start = std::chrono::high_resolution_clock::now();
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        //auto end = std::chrono::high_resolution_clock::now();
        // std::chrono::duration<double, std::milli> elapsed = end-start;
        //std::cout << "Waited " << elapsed.count() << " ms\n";
        LS.Close();
    }
    cv.notify_all();
    ready = false;

    instrument->clearMesures();
    mesures = instrument->getMesures();

}

void SegmentSol::traiter_cmd_queue() {
while (true){
    if (q.size() > 0) {
      cout << "Commande mise au traitement :" << q.front() << endl;
      for (int i = 0; i < 100; i++) {
        trameAtraiter[i] = q.front()[i];
        cout << trameAtraiter[i];
      }
      cout << endl;
      cout << "Traitement de la commande..." << endl;
      q.pop(); //Sortir la commande de la queue
      detramerCommande(); //Détramer la commande afin de la traiter en suivant l'encapsulation
      traiterCommande(); //Traiter la commande utile
    }
  }
}

void SegmentSol::traiterCommande() {

    Reboot* monReboot = new Reboot();

    //Traitement des commandes

    if (commande->getCode() == TypeCommande::MISSION) {
        list<string> typeMission = commande->getParametres();

                vector<string> vector_string;
                   for (auto list : typeMission) {
                        vector_string.push_back(list); //vector_string.at(5) = duree ,vector_string.at(6) = type ;
                        }
                        string duree = vector_string.at(1); //duree
cout<<"duree = "<<duree<<endl;
                        string periode = vector_string.at(3); //période
cout<<"periode = "<<periode<<endl;
                              int int_1 = stoi(duree);
                              int int_2 = stoi(periode);
cout<<"DT de départ = "<<vector_string.at(5)<<endl;
cout<<"type = "<<vector_string.at(6)<<endl;

                            (short)int_1 ;
                            (short)int_2 ;
cout<<"duree2 = "<<int_1<<endl;
cout<<"periode2 = "<<int_2<<endl;

                leSegment->creerMission(int_1,int_2,vector_string.at(5),vector_string.at(6)) ;
                thread lMission = leSegment->tLancerMission();
                lMission.detach();

    } else if (commande->getCode() == TypeCommande::DATE) {
        leSegment->getHorloge(); //setHorloge => 1 argument
    } else if (commande->getCode() == TypeCommande::DEPLOY) {
        //à Voir
    } else if (commande->getCode() == TypeCommande::EMPTY) {
        leSegment->getOrdinateur()->getReboot()->systemeReboot();
    } else if (commande->getCode() == TypeCommande::MEASURE) {
        list<string> mesure = commande->getParametres();
        if (mesure.front() == TypeMisEtat::TEMPCELSIUS) {
            leSegment->effectuerMesure(TEMPCELSIUS);
        } else if (mesure.front() == TypeMisEtat::PIXEL) {
            leSegment->effectuerMesure(PIXEL);
        } else {
				envoyerInfos("ERROR-E11");
		}
    } else if (commande->getCode() == TypeCommande::MEETING) {
        //à Voir
    } else if (commande->getCode() == TypeCommande::SAVE) {
        //à Voir
    } else if (commande->getCode() == TypeCommande::STATUS) {
        list<string> status = commande->getParametres();

		leSegment->obtenirStatus(status);
    } else if (commande->getCode() == TypeCommande::SURVIVAL) {
        //à Voir
    } else
	{
				envoyerInfos("ERROR-E10");
	}
}

thread SegmentSol::tTraiterCommande() {
    return thread([this] {
        detramerCommande();
        traiterCommande();
    });
}

thread SegmentSol::tTraiter_cmd_queue() {
    return thread([this] {
        traiter_cmd_queue();
    });
}

void SegmentSol::envoyerMesure(string type) {
    serialib LS;
    int Ret;
    Instrument* instrument = leSegment->getInstrument();
    unsigned char idSegment = leSegment->getIdentifiant();
	mutex_message.lock();

    message->setIdSegment(idSegment);
	message->setTypeMesure(type);

    if (type.find(FrameManager::TEMPCELSIUS) != string::npos) {
        list<Mesure*> mesures = leSegment->getInstrument()->getMesures();
        message->setMesures(mesures);
        int nbrePaquets = 1;
		ready = true;
		unique_lock<mutex> lck(mutex_serial);
		cv.notify_all();
        for (int i = 0; i < nbrePaquets; i++) {
            tramerMesure(message, nbrePaquets, 1);
			Ret = LS.Open(DEVICE_PORT, 9600);
            Ret = LS.Write(trameEmission, trameEmission[1] + 5);
            LS.Close();
        }
        message->clearMesures();
        instrument->clearLastMesures();
    } else if (type.find(FrameManager::PIXEL) != string::npos) {

        float * mesures = leSegment->getInstrument()->obtenirMesure();
        for (int i = 0; i < 64; i++) {
            message->addPixel(*(mesures + i));
        }
        int nbrePaquets = 8;
		ready = true;
		std::unique_lock<std::mutex> lck(mutex_serial);

        for (int i = 0; i < nbrePaquets; i++) {
            Ret = LS.Open(DEVICE_PORT, 9600);

            tramerMesure(message, nbrePaquets, i + 1);
            Ret = LS.Write(trameEmission, trameEmission[1] + 5);
            LS.Close();
        }
        message->clearPixels();
    }
          cv.notify_all();
          ready = false; //mutex_serial.unlock();

		mutex_message.unlock();

}

void SegmentSol::envoyerInfos(string type){
					message->setIdSegment(leSegment->getIdentifiant());
				vector<char> laTrame = this->tramerRepAcq(message,type);
				vector<char>::iterator it ;
				serialib LS;
				LS.Open(DEVICE_PORT, 9600);
				for (it = laTrame.begin(); it != laTrame.end() ; it++) {
					LS.WriteChar(*it);
				}
				LS.Close();
}
