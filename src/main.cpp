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

int main(int argc, char** argv) {
    
    SegmentVol* segmentVol = new SegmentVol();

    segmentVol->demandeManuelleReboot();
    
    return 0;
}


    
