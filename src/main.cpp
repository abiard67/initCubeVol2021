/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: snir2g1
 *
 * Created on 21 mars 2019, 16:24
 */

#include <cstdlib>
#include "../defs/SegmentVol.h"
#include "../defs/SegmentSol.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    SegmentVol* segmentVol = new SegmentVol();
    SegmentSol* segmentSol = new SegmentSol(segmentVol);
    segmentVol->setSegmentSol(segmentSol);
    segmentVol->setIdentifiant(2);
    list<string> instrument;
    instrument.push_back("-BATT");
    instrument.push_back("-INST");
    instrument.push_back("-BORD");
    instrument.push_back("-CUBE");

    segmentVol->getHorloge()->setRdvTime("2019/04/04 15:25:00");
    segmentVol->creerMission(1, 4, "2019/07/04 15:25:00", "-TC");
    thread t1 = segmentVol->tLancerMission();
    thread t2 = segmentVol->tArretMission();
    segmentVol->configurerRecupEtat(3, instrument);
    thread t3 = segmentVol->recupEtat();
    
    segmentVol->obtenirStatus(&instrument);
    
    string TEMPCELSIUS= "-TC";
    string PIXEL = "-PIX";
    segmentVol->effectuerMesure(TEMPCELSIUS);
    segmentVol->effectuerMesure(PIXEL);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}

