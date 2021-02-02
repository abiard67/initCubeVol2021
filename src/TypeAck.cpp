/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TypeAck.cpp
 * Author: snir2g2
 * 
 * Created on 19 mars 2019, 16:30
 */

#include "../defs/TypeAck.h"
#include <string>



TypeAck::TypeAck() {
}

TypeAck::TypeAck(const TypeAck& orig) {
}

TypeAck::~TypeAck() {
}

string TypeAck::OK = "OK" ;

string TypeAck::FAIL = "FAIL" ;

string TypeAck::BUSY = "BUSY" ;

string TypeAck::ERROR = "ERROR" ;

