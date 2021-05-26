/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SegmentSol.h
 * Author: snir2g2
 *
 * Created on 19 mars 2019, 15:24
 */

#ifndef SEGMENTSOL_H
#define SEGMENTSOL_H

#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "FrameManager.h"
#include "SegmentVol.h"
#include "Message.h"

#define         DEVICE_PORT             "/dev/serial0" 

class SegmentVol;
class SegmentSol: public FrameManager{
public:
    SegmentSol(SegmentVol *leSegment);
    virtual ~SegmentSol();
    void envoyerStatus(list<string> status);
    void envoyerMission();
    void envoyerMesure(string type);
	void envoyerInfos(string type);
    void activerReception();
    thread tActiverReception();
    void traiterCommande();
    thread tTraiterCommande();
    void testEnvoie();
    thread tTestEnvoie();
    
private:
    SegmentVol* leSegment;

};

#endif /* SEGMENTSOL_H */

