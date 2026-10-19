#include "engine/functions.h"
#include "global.h"

// Silver door objects, from 0x02069270 (Set31) to 0x0206930c + 0x6c (door_silver_wait).
typedef struct DoorSilverBlock {
    /* 00 */ u8 unk_00[0x66];
    /* 66 */ u16 unk_66;
    /* 68 */ u16 unk_68;
} DoorSilverBlock;
extern DoorSilverBlock data_0212c75c;
extern u8 data_021349c0[];
extern s16 data_02115c78[][3];
extern EntityFunc set31TypeTable[];
extern EntityFunc doorSilverTable[];

ARM void Set31(Entity *e) {
    set31TypeTable[e->type](e);
}

ARM void door_silver(Entity *e) {
    doorSilverTable[e->action](e);
}
