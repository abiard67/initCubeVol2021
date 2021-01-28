/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mission.h
 * Author: snir2g1
 *
 * Created on 21 mars 2019, 17:18
 */

#ifndef MISSION_H
#define MISSION_H
#include <iostream>
#include <string>
#include "TypeMisEtat.h"

using namespace std;

class Mission : public TypeMisEtat {
public:
    Mission();
    virtual ~Mission();
    void setPeriodicity(short period);
    void setDuration(short duration);
    void setStartTime(string sTime);
    void setMeasureType(string type);
    short getPeriodicity();
    short getDuration();
    string getStartTime();
    string getMeasureType();
private:
    short periodicity;
    short duration;
    string startTime;
    string measureType;
};

#endif /* MISSION_H */

