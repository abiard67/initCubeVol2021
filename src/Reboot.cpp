/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Reboot.cpp
 * Author: Romain
 * 
 * Created on 23 juin 2020, 17:41
 */
#include "../defs/Reboot.h"

Reboot::Reboot() {
    dateHour = "0000/00/00 00:00:00";
    number = 0;
}

Reboot::Reboot(int anbreReboot, string adateHeure) {
    dateHour = adateHeure;
    number = anbreReboot;
}

Reboot::~Reboot() {

}

string Reboot::getDateHour() {
    return this->dateHour;
}

void Reboot::setDateHour(string adateHour) {
    this->dateHour = adateHour;
}

int Reboot::getNumber() {
    return this->number;
}

void Reboot::setNumber(int anumber) {
    this->number = anumber;
}

void Reboot::systemeReboot() {
    system("sudo reboot");
}

void Reboot::resetStatus(){
	dateHour = "0000/00/00 00:00:00";
    number = 0;
}

