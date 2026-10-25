#include "engine/functions.h"
#include "global.h"
#include "engine/sndtrack.h"

// func_020c1a38: runs SndTrack_Update with count on each active track of the table.
extern "C" void func_020c1a38(s32 count);
ARM void func_020c1a38(s32 count) {
    s32 i;
    SndTrack *track;

    for (i = 0; i < 4; i++) {
        track = &data_02184920[i];
        if (((s32)(track->flags << 31) >> 31) != 0) {
            SndTrack_Update(track, count);
        }
    }
}
