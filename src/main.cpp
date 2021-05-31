#include <cstdlib>
#include "../defs/SegmentVol.h"
#include "../defs/SegmentSol.h"
#include <thread>

using namespace std;

int main(int argc, char** argv) {

    SegmentVol* segmentVol = new SegmentVol();
    segmentVol->setIdentifiant(1);
    SegmentSol* monSeg = new SegmentSol(segmentVol);
	segmentVol->setSegmentSol(monSeg);
    thread t1 = monSeg->tActiverReception();

    t1.join();
    return 0;
}
