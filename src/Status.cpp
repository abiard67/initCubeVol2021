/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Status.cpp
 * Author: snir2g2
 * 
 * Created on 14 mars 2019, 17:39
 */

#include "../defs/Status.h"

Status::Status() {
	this->OnOff=true;
	this->mode=SLEEP;
    error=0;
    temperature=0;
}

Status::Status(const Status& orig) {
}

Status::~Status() {
}

void Status::setMode(Mode mode) {
    this->mode = mode;
}

float Status::getTemp() {
    return temperature;
}


Mode Status::getMode() {
    return mode;
}

void Status::setOnOff(bool OnOff) {
    this->OnOff = OnOff;
}

int Status::getError() {
    return error;
}

bool Status::getOnOff() {
    return OnOff;
}

void Status::setTemp(float Temp){
    temperature = Temp;
}

