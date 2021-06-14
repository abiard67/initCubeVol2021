/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Magnetometre.cpp
 * Author: LucasG
 *
 * Created on 31 mars 2020, 15:51
 */

#include "../defs/Magnetometre.h"

Magnetometre::Magnetometre() {
}

Magnetometre::Magnetometre(const Magnetometre& orig) {
}

Magnetometre::~Magnetometre() {
}

void Magnetometre::activer(){

}

void Magnetometre::desactiver(){
    // Pointeur vers le registre CNTL1 et le bit MODE0 //
char mode[]={0x0A,0x00};



}


float Magnetometre::calculerTempInst(char aoctetLow, char aoctetHigh) {

float resultat;
	short TempInstr;

	//Reconstitution sur 16 bits de l'information

	//transformation en float
	resultat=TempInstr;

	//Test bit de signe
	if ((TempInstr & 0x800)==0) //si signe positif
		resultat = resultat*0.0625;
	else
	{
		TempInstr= TempInstr & 0x7FF;
		resultat = TempInstr;
		resultat =-1*resultat *0.0625;
	}

	return resultat;
}

void Magnetometre::PassThrough() {

// Ouverture du chemin //
int N = open("/dev/i2c-1",O_RDWR);
//
int addr = 0x69;
int state = ioctl (N, I2C_SLAVE, addr);
//
//// Pointeur vers le registre INT_PIN_CFG et le bit BYPASS_EN //
char commande[]={0x37,0x2};
//
char reponse[1];

//// Positionnement du curseur sur le registre INT_PIN_CFG //
write(N,commande,1);

//// Lecture du contenu du registre //
read(N,reponse,1);

// Positionnement du curseur sur le bit BYPASS_EN //
commande[1]=reponse[0] | 0x2;

//// Modification du registre INT_PIN_CFG //
write(N,commande,2);

int magneto = 0x0C;

//int state1 = ioctl (N, I2C_SLAVE, magneto);
   }
bool Magnetometre::LireDonnee(){

	champX = 35;
	champY = 2;
	champZ = 3;
	return true;
	}
void Magnetometre::getChamp(short champ [3]){
	champ[0] = champX;
	champ[1] = champY;
	champ[2] = champZ;
}


