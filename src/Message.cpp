/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Message.cpp
 * Author: snir2g2
 * 
 * Created on 19 mars 2019, 15:37
 */
#include <iomanip>
#include <sstream>

#include "../defs/Message.h"


using namespace std ;

Message::Message() {
	typeMission = "";

	microSDenMo = "0";
	RAMenPourcent = "0";
	temperatureProc = "0.0";
	dateOrdinateur = "0000/00/00 00:00:00" ;
	chargeBat = "0";
	voltageBat= "0";
	amperageBat= "0";
	chargeStatus = false;
	temperatureBat= "0";
	capacityBat= "0";
	statInstrument = new Status();
	/**
	 * Cet attribut correspond à la température du cube, entre les cartes.
	 */
	temperatureCube= "0";
	reboot = new Reboot();  
	////////// Modification depuis la dernière fois pour récupérer cette information
	typeMesure = "";
}

Message::Message(const Message& orig) {
  
}

Message::~Message() {
}

unsigned char Message::getIdSegment(){
	return idSegment;  
}


list<Mesure*> Message::getMesures(){
	return mesures;
}

string Message::getTypeMission() { 
	return this->typeMission;
}


void Message::setIdSegment(unsigned char id){
	this->idSegment=id;  
}

void Message::setMesures(list<Mesure*> mesures){
    this->mesures=mesures;
}

void Message::clearMesures(){
	this->mesures.clear();
}

void Message::setTypeMission(string typeMission) {
	this->typeMission=typeMission;
}

string Message::getMicroSDenMo() {
	return this->microSDenMo;
}

void Message::setMicroSDenMo(string amicroSDenMo) {
	this->microSDenMo = amicroSDenMo;
}

string Message::getRAMenPourcent() {
	return this->RAMenPourcent;
}

void Message::setRAMenPourcent(string aRAMenPourcent) {
	this->RAMenPourcent = aRAMenPourcent;
}

string Message::getTemperatureProc() {
	return this->temperatureProc;
}

void Message::setTemperatureProc(float atemperatureProc) {
	stringstream stream;
	stream << fixed << setprecision(1) <<  atemperatureProc;
	temperatureProc=stream.str();
}

string Message::getDateOrdinateur() {
	return this->dateOrdinateur;
}

void Message::setDateOrdinateur(string adateOrdinateur) {
	this->dateOrdinateur = adateOrdinateur;
}

string Message::getChargeBat() {
	return this->chargeBat;
}

void Message::setChargeBat(char achargeBat) {
	stringstream stream;
	stream << (short)achargeBat;
	chargeBat=stream.str();
}

string Message::getAmperageBat() {
	return this->amperageBat;
}

void Message::setAmperageBat(short aamperageBat) {
	stringstream stream;
	stream << aamperageBat;
	amperageBat=stream.str();	
}

bool Message::getChargeStatus() {
	return this->chargeStatus;
}

void Message::setChargeStatus(bool achargeStatus) {
	this->chargeStatus = achargeStatus;
}

string Message::getTemperatureBat() {
	return this->temperatureBat;
}

void Message::setTemperatureBat(float atemperatureBat) {
	stringstream stream;
	stream << fixed << setprecision(1) <<  atemperatureBat;
	temperatureBat=stream.str();	
}

string Message::getVoltageBat() {
	return this->voltageBat;
}

void Message::setVoltageBat(float avoltageBat) {
	stringstream stream;
	stream << fixed << setprecision(1) <<  avoltageBat;
	voltageBat=stream.str();
}

string Message::getCapacityBat() {
	return this->capacityBat;
}

string Message::getTypeMesure(){
	return this->typeMesure;
}

void Message::setCapacityBat(short acapacityBat) {
	stringstream stream;
	stream << acapacityBat;
	capacityBat=stream.str();	
}

Status* Message::getStatInstrument() {
	return this->statInstrument;
}

list<string> Message::getPixels(){
	return this->pixels;
}

void Message::setStatInstrument(Status* astatInstrument) {
	this->statInstrument = astatInstrument;
}

string Message::getTemperatureCube() {
	return this->temperatureCube;
}

void Message::setTemperatureCube(float atemperatureCube) {
	stringstream stream;
	stream  << fixed << setprecision(1) << atemperatureCube;
	temperatureCube=stream.str();	
}

Reboot* Message::getReboot() {
	return this->reboot;
}

void Message::setReboot(Reboot* areboot) {
	this->reboot = areboot;
}

void Message::setTypeMesure(string type){
	this->typeMesure=type;
}

void Message::addPixel(float leReleve){

	stringstream stream;
	stream << fixed << setprecision(1) << leReleve;
	this->pixels.push_back(stream.str());	

}

void Message::clearPixels()
{
	this->pixels.clear();

}

void Message::setPixels(list<string> lesNouveauxPixels)
{
	this->pixels=lesNouveauxPixels;
}

