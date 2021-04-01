#include <cstdlib>
#include "../defs/SegmentVol.h"
#include "../defs/SegmentSol.h"
#include <thread>

using namespace std;

int main(int argc, char** argv) {

    cout << "Main 1" << endl;
    SegmentVol* segmentVol = new SegmentVol();
    cout << "Main 2" << endl;
    segmentVol->setIdentifiant(1);
    cout << "Main 3" << endl;
    SegmentSol* monSeg = new SegmentSol(segmentVol);
    cout << "Main 4" << endl;

    thread t1 = monSeg->tActiverReception();
    cout << "Main 5" << endl;
    //thread t2 = monSeg->tTestEnvoie();
    //thread t3 = monSeg->tTraiterCommande();

    t1.join();
    cout << "Main 6" << endl;
    //t2.join();
    //t3.join();

    return 0;





    /* SegmentVol* segmentVol = new SegmentVol();

     segmentVol->demandeManuelleReboot();

     return 0;*/
}



