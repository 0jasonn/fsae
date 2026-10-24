#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/player.h"

// Check tables (module check). Original names from the debug build: CheckInit, CheckPlsSet (both plain).

// One 0x90-byte slot of the check table data_0212e590: a link word (rotated by CheckInit) and a flag byte.
typedef struct CheckSlot {
    u8 unk_00[8];
    u32 link;
    u8 flag;
    u8 unk_0d[0x83];
} CheckSlot;

extern CheckSlot data_0212e590[16];
extern void *data_0213490c;

extern "C" void CheckInit(void);
extern "C" void CheckPlsSet(void);

// Clears the flag of all 16 slots, then rotates the link words by the player count (swaps for 2, rotations for 3 and 4).
ARM void CheckInit(void) {
    u32 saved;

    data_0212e590[0].flag = 0;
    data_0212e590[1].flag = 0;
    data_0212e590[2].flag = 0;
    data_0212e590[3].flag = 0;
    data_0212e590[4].flag = 0;
    data_0212e590[5].flag = 0;
    data_0212e590[6].flag = 0;
    data_0212e590[7].flag = 0;
    data_0212e590[8].flag = 0;
    data_0212e590[9].flag = 0;
    data_0212e590[10].flag = 0;
    data_0212e590[11].flag = 0;
    data_0212e590[12].flag = 0;
    data_0212e590[13].flag = 0;
    data_0212e590[14].flag = 0;
    data_0212e590[15].flag = 0;
    switch (data_0212c7c8.unk_0) {
    case 2:
        saved = data_0212e590[0].link;
        data_0212e590[0].link = data_0212e590[1].link;
        data_0212e590[1].link = saved;
        break;
    case 3:
        saved = data_0212e590[0].link;
        data_0212e590[0].link = data_0212e590[1].link;
        data_0212e590[1].link = data_0212e590[2].link;
        data_0212e590[2].link = saved;
        break;
    case 4:
        saved = data_0212e590[0].link;
        data_0212e590[0].link = data_0212e590[1].link;
        data_0212e590[1].link = data_0212e590[2].link;
        data_0212e590[2].link = data_0212e590[3].link;
        data_0212e590[3].link = saved;
        break;
    }
}

// Passes the entities of players 1 to 3 to func_02084180 while they exist, after setting up the list head of data_0212e590.
ARM void CheckPlsSet(void) {
    Entity *first;

    func_02029a50(data_0212e590, 0x900);
    ((u32 *)data_0212e590)[0] = (u32)data_0212e590;
    first = data_0212ceb0[0].entity;
    ((u32 *)data_0212e590)[1] = (u32)data_0212e590;
    data_0213490c = data_0212e590;
    ((u32 *)data_0212e590)[2] = (u32)first;
    if (data_0212ceb0[1].entity == NULL) {
        return;
    }
    func_02084180(data_0212ceb0[1].entity);
    if (data_0212ceb0[2].entity == NULL) {
        return;
    }
    func_02084180(data_0212ceb0[2].entity);
    if (data_0212ceb0[3].entity == NULL) {
        return;
    }
    func_02084180(data_0212ceb0[3].entity);
}
