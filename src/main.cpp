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
    thread t2 = monSeg->tTraiter_cmd_queue();

    t1.join();
    t2.join();
    return 0;
}
