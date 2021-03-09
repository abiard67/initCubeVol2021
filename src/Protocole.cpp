/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Protocole.cpp
 * Author: snir2g2
 * 
 * Created on 18 mars 2019, 08:36
 */

#include <iomanip>
#include <sstream>
#include "../defs/Protocole.h"
#include "../defs/serialib.h"
#include "../defs/Status.h"
#include "../defs/Commande.h"

using namespace std;

string Protocole::ERR_CHECKSUM = "ERR_C";
string Protocole::ERR_FORMAT = "ERR_F";

int Protocole::pause = 1000;

Protocole::Protocole() {
    commande = new Commande();

}

Protocole::Protocole(const Protocole& orig) {
}

Protocole::~Protocole() {
}

int Protocole::getNbrePaquets() {
    return this->nbrePaquets;
}

int Protocole::getNumPaquet() {
    return this->numPaquet;
}

list<vector<char>> Protocole::getReceived() {
    return this->received;
}

void Protocole::setTableau(char laDataRecu[100]) {
    for (int i = 0; i < 100; i++) {
        this->tableau[i] = laDataRecu[i];
    }
}

void Protocole::calculerChecksum(char & PF, char & pf) {
    short Checksum = 0;
    char leChecksum[2];

    for (int i = 1; i < tableau[2] + 3; i++) {
        Checksum = Checksum^tableau[i];
    }
    sprintf(leChecksum, "%2X", Checksum);
    if (leChecksum[0] == 32) leChecksum[0] = '0';
    if (leChecksum[1] == 32) leChecksum[1] = '0';
    PF = leChecksum[0];
    pf = leChecksum[1];

}

void Protocole::extraireCommande(char reception[]) {

    vector <char> trame(0);
    for (int i = 0; i <= 104; i++) {

        trame.push_back(reception[i]);

    }

    vector<char>::iterator it = trame.begin();
    string cmdReception;

    advance(it, 3);

    for (int i = 0; *it != '-'; i++) {

        cmdReception.push_back(*it);
        advance(it, 1);

    }

    commande->setCode(cmdReception);
}

void Protocole::extraireParametres(char reception[]) {

    vector <char>trame(0)
   
    
    for (int i = 0; i <= trame[2]+2; i++) {       
                trame.push_back(reception[i]);
                   
    } 
    
    vector<string> arguments;   
     vector<char>::iterator it = trame.begin();
     
     string arg="";
     char elem ='-';
     
    
    
     if(it!=trame.end()){
    
        for(it = trame.begin();it!=trame.end();++it){
          
        if (*it==elem){
            
        do
        {
                it++;
            arg=arg+*(it);
          }
        while((*(it+1)!=elem) &&(it!=trame.end()-1)) ;      
          
          arguments.push_back(arg);
          cout<< arg<<endl;
                     
         
        }     
       }   
     }
       
     
     return arguments;

}

bool Protocole::verifierChecksum() {
    char PF;
    char pf;
    char cheksumRecuPF, cheksumRecupf;
    cheksumRecuPF = tableau[tableau[2] + 3];
    cheksumRecupf = tableau[tableau[2] + 4];
    calculerChecksum(PF, pf);
    if ((cheksumRecuPF != PF) || (cheksumRecupf != pf)) return false;
    else return true;
}

unsigned char Protocole::calculerNombrePaquets(Message * message) {
    list<Mesure*> listeDeMesures = message->getMesures();
    int nbreTotalMesures = listeDeMesures.size();
    if (message->getTypeMission() == TypeMisEtat::TEMPCELSIUS) {
        this->nbrePaquets = nbreTotalMesures / 2;
    }
    return nbrePaquets;
}

/**
 *  /~/id/nbre octets/"MISSION"/nbrepaquets/numPaquet/ Ttemp1/ -DTdate1/ Ttemp2/ -DTdate2/CheksumPF/cheksumpf
 *
 */
void Protocole::tramerMission(Message* message, int nbrePaquets, int numPaquet) {
    char tab[20] = {};
    char PF;
    char pf;


    unsigned int j;

    Mesure *lamesure;
    list<Mesure*> laListe;
    list<Mesure*>::iterator lIndice;
    string valeurMesure, dateHour;
    stringstream stream;

    tableau[0] = '~';
    tableau[1] = message->getIdSegment();
    tableau[2] = 98; //Valeur provisoire en attendant la fin de construction du message.
    strcpy(tab, TypeCommande::MISSION.c_str());
    for (j = 0; j < TypeCommande::MISSION.size(); j++) {
        tableau[3 + j] = tab[j];
    }

    j = j + 3;

    tableau[j] = nbrePaquets;
    j++;
    tableau[j] = numPaquet;
    j++;

    strcpy(tab, message->getTypeMission().c_str());

    for (unsigned int k = 0; k < message->getTypeMission().size(); k++) {
        tableau[j] = tab[k];
        j++;
    }

    //Pour cet incr�ment, seule la mission temp�rature peut �tre lanc�e
    if (message->getTypeMission() == TypeMisEtat::TEMPCELSIUS) {
        laListe = message->getMesures();

        /*************** Traitement de la premi�re donn�e ********************/
        tableau[j] = ' ';
        j++;
        strcpy(tab, TypeMisEtat::TEMPERATURE.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::TEMPERATURE.size(); k++) {
            tableau[j] = tab[k];
            j++;
        }

        lIndice = laListe.begin();
        lamesure = *lIndice; //On met dans la variable lamesure le contenu de l'it�rateur
        stream << fixed << setprecision(1) << lamesure->getMesure();
        valeurMesure = stream.str();
        strcpy(tab, valeurMesure.c_str());
        for (unsigned int k = 0; k < valeurMesure.size(); k++) {
            tableau[j] = tab[k];
            j++;
        }
        tableau[j] = ' ';
        j++;
        strcpy(tab, TypeMisEtat::DATETIME.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::DATETIME.size(); k++) {
            tableau[j] = tab[k];
            j++;
        }
        dateHour = lamesure->getDateHour();
        strcpy(tab, dateHour.c_str());
        for (unsigned int k = 0; k < dateHour.size(); k++) {
            tableau[j] = tab[k];
            j++;
        }
        laListe.pop_front(); //On supprime la donn�e trait�e

        /*************** Traitement de la deuxi�me donn�e ********************/
        tableau[j] = ' ';
        j++;
        strcpy(tab, TypeMisEtat::TEMPERATURE.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::TEMPERATURE.size(); k++) {
            tableau[j] = tab[k];
            j++;
        }

        lIndice = laListe.begin();
        lamesure = *lIndice; //On met dans la variable lamesure le contenu de l'it�rateur
        stream.str(""); //On vide le flux
        stream << fixed << setprecision(1) << lamesure->getMesure();
        valeurMesure = stream.str();
        strcpy(tab, valeurMesure.c_str());
        for (unsigned int k = 0; k < valeurMesure.size(); k++) {
            tableau[j] = tab[k];
            j++;
        }
        tableau[j] = ' ';
        j++;
        strcpy(tab, TypeMisEtat::DATETIME.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::DATETIME.size(); k++) {
            tableau[j] = tab[k];
            j++;
        }
        dateHour = lamesure->getDateHour();
        strcpy(tab, dateHour.c_str());
        for (unsigned int k = 0; k < dateHour.size(); k++) {
            tableau[j] = tab[k];
            j++;
        }
        laListe.pop_front();

        /** Mise � jour de la liste **/
        message->setMesures(laListe);
    }

    /** Mise � jour du champ "nombre d'octets" **/
    tableau[2] = j - 3; //ATTENTION A VERIFIER

    calculerChecksum(PF, pf);
    tableau[j] = PF;
    j++;
    tableau[j] = pf;
    j++;
    tableau[j] = '\n';
    j++;
    for (j = j; j < 100; j++)
        tableau[j] = 0;

}

void Protocole::ajouterDataOrdiBord(Message* amessage, unsigned int &aposition) {
    char tab[20] = {};
    strcpy(tab, TypeAppareil::ORDIBORD.c_str());
    for (unsigned int k = 0; k < TypeAppareil::ORDIBORD.size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, TypeMisEtat::STOCKMO.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::STOCKMO.size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, amessage->getMicroSDenMo().c_str());
    for (unsigned int k = 0; k < amessage->getMicroSDenMo().size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }

    strcpy(tab, TypeMisEtat::RAMPOURCENT.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::RAMPOURCENT.size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, amessage->getRAMenPourcent().c_str());
    for (unsigned int k = 0; k < amessage->getRAMenPourcent().size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    tableau[aposition] = ' ';
    aposition++;
    strcpy(tab, TypeMisEtat::TEMPERATURE.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::TEMPERATURE.size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }

    strcpy(tab, amessage->getTemperatureProc().c_str());
    for (unsigned int k = 0; k < amessage->getTemperatureProc().size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    tableau[aposition] = ' ';
    aposition++;
    strcpy(tab, TypeMisEtat::DATETIME.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::DATETIME.size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, amessage->getDateOrdinateur().c_str());
    for (unsigned int k = 0; k < amessage->getDateOrdinateur().size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
}

void Protocole::ajouterDataBattery(Message* amessage, unsigned int &aposition) {
    char tab[20] = {};
    strcpy(tab, TypeAppareil::BATTERIE.c_str());
    for (unsigned int k = 0; k < TypeAppareil::BATTERIE.size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, TypeMisEtat::CHARGE.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::CHARGE.size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, amessage->getChargeBat().c_str());
    for (unsigned int k = 0; k < amessage->getChargeBat().size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, TypeMisEtat::VOLTAGE.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::VOLTAGE.size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, amessage->getVoltageBat().c_str());
    for (unsigned int k = 0; k < amessage->getVoltageBat().size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, TypeMisEtat::AMPERAGE.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::AMPERAGE.size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, amessage->getAmperageBat().c_str());
    for (unsigned int k = 0; k < amessage->getAmperageBat().size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    if (amessage->getChargeStatus()) {
        strcpy(tab, TypeMisEtat::LOAD.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::LOAD.size(); k++) {
            tableau[aposition] = tab[k];
            aposition++;
        }
    }

    tableau[aposition] = ' ';
    aposition++;
    strcpy(tab, TypeMisEtat::TEMPERATURE.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::TEMPERATURE.size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    strcpy(tab, amessage->getTemperatureBat().c_str());
    for (unsigned int k = 0; k < amessage->getTemperatureBat().size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    tableau[aposition] = ' ';
    aposition++;
}

void Protocole::ajouterStatusInst(Message* amessage, unsigned int &aposition) {
    char tab[20] = {};
    strcpy(tab, TypeAppareil::INSTRUMENT.c_str());
    for (unsigned int k = 0; k < TypeAppareil::BATTERIE.size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    Status * leStatus = amessage->getStatInstrument();
    if (leStatus->getOnOff() == true) {
        strcpy(tab, TypeMisEtat::ON.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::ON.size(); k++) {
            tableau[aposition] = tab[k];
            aposition++;
        }
    } else {
        strcpy(tab, TypeMisEtat::OFF.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::OFF.size(); k++) {
            tableau[aposition] = tab[k];
            aposition++;
        }
    }

    if (leStatus->getMode() == Mode::NORMAL) {
        strcpy(tab, TypeMisEtat::NORMAL.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::NORMAL.size(); k++) {
            tableau[aposition] = tab[k];
            aposition++;
        }
    } else if (leStatus->getMode() == Mode::SLEEP) {
        strcpy(tab, TypeMisEtat::SLEEP.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::SLEEP.size(); k++) {
            tableau[aposition] = tab[k];
            aposition++;
        }
    } else if (leStatus->getMode() == Mode::STAND_BY) {
        strcpy(tab, TypeMisEtat::STANDBY.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::STANDBY.size(); k++) {
            tableau[aposition] = tab[k];
            aposition++;
        }
    }

    tableau[aposition] = ' ';
    aposition++;
    strcpy(tab, TypeMisEtat::TEMPERATURE.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::TEMPERATURE.size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    stringstream stream;
    stream << fixed << setprecision(1) << leStatus->getTemp();
    strcpy(tab, stream.str().c_str());
    for (unsigned int k = 0; k < stream.str().size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    tableau[aposition] = ' ';
    aposition++;
}

void Protocole::ajouterStatusCube(Message* amessage, unsigned int &aposition) {
    char tab[20] = {};

    strcpy(tab, TypeAppareil::CUBE.c_str());
    for (unsigned int k = 0; k < TypeAppareil::CUBE.size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }
    tableau[aposition] = ' ';
    aposition++;

    strcpy(tab, TypeMisEtat::TEMPERATURE.c_str());
    for (unsigned int k = 0; k < TypeMisEtat::TEMPERATURE.size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }

    strcpy(tab, amessage->getTemperatureCube().c_str());

    for (unsigned int k = 0; k < amessage->getTemperatureCube().size(); k++) {
        tableau[aposition] = tab[k];
        aposition++;
    }

    tableau[aposition] = ' ';
    aposition++;

    if (amessage->getReboot()->getNumber() > 0) {
        strcpy(tab, TypeAppareil::REBOOT.c_str());
        for (unsigned int k = 0; k < TypeAppareil::REBOOT.size(); k++) {
            tableau[aposition] = tab[k];
            aposition++;
        }

        strcpy(tab, TypeMisEtat::DATETIME.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::DATETIME.size(); k++) {
            tableau[aposition] = tab[k];
            aposition++;
        }

        strcpy(tab, amessage->getReboot()->getDateHour().c_str());
        for (unsigned int k = 0; k < amessage->getReboot()->getDateHour().size(); k++) {
            tableau[aposition] = tab[k];
            aposition++;
        }

        strcpy(tab, TypeMisEtat::REBOOT_NUMBER.c_str());
        for (unsigned int k = 0; k < TypeMisEtat::REBOOT_NUMBER.size(); k++) {
            tableau[aposition] = tab[k];
            aposition++;
        }

        strcpy(tab, to_string(amessage->getReboot()->getNumber()).c_str());
        for (unsigned int k = 0; k < to_string(amessage->getReboot()->getNumber()).size(); k++) {
            tableau[aposition] = tab[k];
            aposition++;

        }
    }

}

/**
 *  /~/id/nbre octets/"STATUS"/nbrepaquets/numPaquet/................../CheksumPF/cheksumpf/'\n'
 *  /~/id/nbre octets/"STATUS"/2	1	/-BORD/-SMo/-S6553/ -T47/ -DT2019/02/13 12:12:36/-BATT/-C85/-V4,1/-A950/-LOAD/ -T25,0 /CheksumPF/cheksumpf/'\n'
 *  /~/id/nbre octets/"STATUS"/2	2	/-INST/-ON/-STBY60/ -T25,8/ -CUBE/ -T26,4 /-REBOOT/-DT2019/02/13 12:12:36/-N1/CheksumPF/cheksumpf/'\n'
 *
 */
void Protocole::tramerStatus(Message* message, int nbrePaquets, int numPaquet) {
    char tab[20] = {};
    char PF;
    char pf;
    unsigned int j;

    string valeurMesure, dateHour;
    stringstream stream;

    tableau[0] = '~';
    tableau[1] = message->getIdSegment();
    tableau[2] = 98; //Valeur provisoire en attendant la fin de construction du message.
    strcpy(tab, TypeCommande::STATUS.c_str());
    for (j = 0; j < TypeCommande::STATUS.size(); j++) {
        tableau[3 + j] = tab[j];
    }
    j = j + 3;
    tableau[j] = nbrePaquets;
    j++;
    tableau[j] = numPaquet;
    j++;
    if (numPaquet == 1) {
        ajouterDataOrdiBord(message, j);
        ajouterDataBattery(message, j);
    } else {
        ajouterStatusInst(message, j);
        ajouterStatusCube(message, j);
    }

    /** Mise � jour du champ "nombre d'octets" **/
    tableau[2] = j - 3; //ATTENTION A VERIFIER

    calculerChecksum(PF, pf);
    tableau[j] = PF;
    j++;
    tableau[j] = pf;
    j++;
    tableau[j] = '\n';
    j++;
    for (j = j; j < 100; j++)
        tableau[j] = 0;

}

void Protocole::tramerMesure(Message* message, int nbrePaquets, int numPaquet) {

    list<string>::iterator lIndice;
    char tab[20] = {};
    char PF;
    char pf;
    unsigned int j = 0, nbrePixels = 0;

    tableau[0] = '~';
    tableau[1] = message->getIdSegment();
    tableau[2] = 98; //Valeur provisoire en attendant la fin de construction du message.

    strcpy(tab, TypeCommande::MEASURE.c_str());
    for (j = 0; j < TypeCommande::MEASURE.size(); j++) {
        tableau[3 + j] = tab[j];
    }

    j = j + 3;

    tableau[j] = nbrePaquets;
    j++;
    tableau[j] = numPaquet;
    j++;

    strcpy(tab, message->getTypeMesure().c_str());

    for (unsigned int k = 0; k < message->getTypeMesure().size(); k++) {
        tableau[j] = tab[k];
        j++;
    }
    if (message->getTypeMesure() == TypeMisEtat::PIXEL) {
        list<string> lesPixels = message->getPixels();

        for (lIndice = lesPixels.begin(); lIndice != lesPixels.end(); lIndice++) {
            tableau[j] = ' ';
            j++;
            //cout<< (*lIndice) << " ";
            strcpy(tab, (*lIndice).c_str());
            for (unsigned int k = 0; k < (*lIndice).size(); k++) {
                tableau[j] = tab[k];

                j++;
            }
            //lesPixels.erase(lIndice);

            //--lIndice;

            nbrePixels = nbrePixels + 1;

            if (nbrePixels == 8) break; // sortie tous les 8 pixels.

        }
        lesPixels.erase(lesPixels.begin(), lIndice);
        message->setPixels(lesPixels);
    } else if (message->getTypeMesure() == TypeMisEtat::TEMPCELSIUS) {
        list<Mesure*> mesures = message->getMesures();

        float releve = mesures.back()->getMesure();
        stringstream stream;
        stream << fixed << setprecision(1) << releve;

        strcpy(tab, (stream.str()).c_str());
        tableau[j] = ' ';
        j++;
        for (unsigned int k = 0; k < (stream.str()).size(); k++) {
            tableau[j] = tab[k];
            j++;
        }
    }
    tableau[j] = ' ';

    j++;
    tableau[2] = j - 3; //ATTENTION A VERIFIER

    calculerChecksum(PF, pf);
    tableau[j] = PF;

    j++;
    tableau[j] = pf;

    j++;
    tableau[j] = '\n';
    j++;
    for (j = j; j < 100; j++)
        tableau[j] = 0;


}

string Protocole::extraireTypeMessage(int &pos) {
    string typeMessage = "";
    bool OK = false;
    int i;

    i = 0;
    for (vector<char>::iterator it = (received.front()).begin(); it != (received.front()).end(); ++it) {
        if ((i == 0)&&(*it == '~')) {
            OK = true;
        }
        if (OK == true) {
            tableau[i] = *it;
            i = i + 1;
            if (i == 100) break;
        }
    }
    //if ((received.front()).front()=='~')
    //{
    //}
    if (tableau[0] == '~') {
        OK = verifierChecksum();
        if (!OK) return Protocole::ERR_CHECKSUM;
        for (i = 3; i < 11; i++) {
            if ((tableau[i] > 0x41) && (tableau[i] < 0x7A)) typeMessage = typeMessage + tableau[i];
            else {
                pos = i;
                break;
            }
        }
        extraireNombrePaquets(pos);
        return typeMessage;
    } else return Protocole::ERR_FORMAT;
}

void Protocole::extraireNombrePaquets(int &pos) {
    this->nbrePaquets = tableau[pos];
    this->numPaquet = tableau[pos + 1];
    pos = pos + 2;
}

int Protocole::calculerNbrePaquetsSalve() {
    return received.size();
}

string Protocole::extraireTypeDataMission(int &pos) {
    int i;
    string typeDataMission = "-";
    for (i = pos; i < pos + 7; i++) {
        if ((tableau[i] > 0x41) && (tableau[i] < 0x7A)) typeDataMission = typeDataMission + tableau[i];
        if (((i != pos)&&(tableau[i] == '-')) || (tableau[i] == ' ')) {
            pos = i;
            break;
        }
    }
    if (typeDataMission.size() == 1) return Protocole::ERR_FORMAT;
    else return typeDataMission;
}

int Protocole::extraireDataMission(list<float> &datas, list<string> &dateHours, int &pos, string typeMission) {
    unsigned int positionData = 0, taille, posSeparateur = 0;
    string donnee;
    stringstream sdonnee;
    float fdonnee;
    string zoneDonnees = string(tableau).substr(pos, tableau[2] + 2);
    if (typeMission == Protocole::TEMPCELSIUS) {
        do {
            positionData = zoneDonnees.find(Protocole::TEMPERATURE, posSeparateur);
            if (positionData != std::string::npos) {
                posSeparateur = zoneDonnees.find(" ", positionData);
                if (posSeparateur != std::string::npos) {
                    taille = posSeparateur - positionData - Protocole::TEMPERATURE.size();
                    donnee = zoneDonnees.substr(positionData + Protocole::TEMPERATURE.size(), taille);
                    sdonnee.clear();
                    sdonnee << donnee;
                    sdonnee>>fdonnee;
                    datas.push_back(fdonnee);
                    positionData = zoneDonnees.find(Protocole::DATETIME, posSeparateur);
                    if (positionData != std::string::npos) {
                        posSeparateur = zoneDonnees.find(" ", positionData);
                        if (posSeparateur != std::string::npos) {
                            posSeparateur = zoneDonnees.find(" ", posSeparateur + 1);
                            if (posSeparateur != std::string::npos) {
                                taille = posSeparateur - positionData - Protocole::DATETIME.size();
                                donnee = zoneDonnees.substr(positionData + Protocole::DATETIME.size(), taille);
                                dateHours.push_back(donnee);
                            } else {
                                posSeparateur = zoneDonnees.size() - 1;
                                taille = posSeparateur - positionData - Protocole::DATETIME.size();
                                donnee = zoneDonnees.substr(positionData + Protocole::DATETIME.size(), taille);
                                dateHours.push_back(donnee);
                                return 1;
                            }
                        } else {
                            return -1;
                        }
                    } else {
                        return -1;
                    }
                } else {
                    return -1;
                }

            } else {
                return -1;
            }
        } while (posSeparateur < zoneDonnees.size() - 1);
    }
    return 1;
}

void Protocole::addReceived(char recu [100]) {
    vector<char> uneTrame(recu, recu + 100);
    received.push_back(uneTrame);
}

void Protocole::supprimerPaquet() {
    this->received.pop_front();
}


