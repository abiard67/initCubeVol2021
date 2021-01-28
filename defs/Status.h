/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Status.h
 * Author: snir2g2
 *
 * Created on 14 mars 2019, 17:39
 */

#ifndef STATUS_H
#define STATUS_H
#include "../defs/Mode.h"

class Status {
public:
	//enum Mode {NORMAL, SLEEP, STAND_BY};

    Status();
    Status(const Status& orig);
    virtual ~Status();
    void setMode(Mode mode);
    Mode getMode();
    float getTemp();
    int getError();
    void setOnOff(bool OnOff);
    bool getOnOff();
    void setTemp(float Temp);
    
private:
    bool OnOff;
    int error;
    Mode mode;
    float temperature;
    

};

#endif /* STATUS_H */

