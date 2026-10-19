#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/objdecls_a.h"

extern u8 localPlayerIndex;            // localPlayerIndex

// MapMarkerSet, 0x02069d64: makes the map markers for each player and links the local player's marker to its child.
ARM void MapMarkerSet(void) {
    Entity *found;
    Entity *marker;
    u8 i;
    GetSetWorkSp(0x32, 1, 0);
    GetSetWorkSp(0x32, 3, 0);
    i = 0;
    while (i < data_0212c7c8.unk_0) {
        found = GetSetWorkSp(0x32, 2, i);
        if (found != 0) {
            if (i == localPlayerIndex) {
                marker = GetSetWorkSp(0x32, 0, 0);
                if (marker != 0) {
                    marker->child = found;
                }
            }
        }
        i++;
    }
}
