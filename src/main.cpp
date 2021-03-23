#include <cstdlib>
#include "../defs/SegmentVol.h"
#include "../defs/SegmentSol.h"
#include <thread>

using namespace std;

int main(int argc, char** argv) {


    SegmentVol* segmentVol = new SegmentVol();
    segmentVol->setIdentifiant(1);
    SegmentSol* monSeg = new SegmentSol(segmentVol);

    thread t1 = monSeg->tActiverReception();
    thread t2 = monSeg->tTestEnvoie();
    thread t3 = monSeg->tTraiterCommande();

    t1.join();
    t2.join();
    t3.join();

    return 0;





    /* SegmentVol* segmentVol = new SegmentVol();

     segmentVol->demandeManuelleReboot();

     return 0;*/
}



