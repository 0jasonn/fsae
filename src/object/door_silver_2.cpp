#include "engine/functions.h"
#include "global.h"

typedef struct DoorSilverBlock {
    /* 00 */ u8 unk_00[0x66];
    /* 66 */ u16 unk_66;
    /* 68 */ u16 unk_68;
} DoorSilverBlock;
extern DoorSilverBlock data_0212c75c;
extern u8 data_021349c0[];

ARM void door_silver_wait(Entity *e) {
    if (data_021349c0[8] < 3) {
        return;
    }
    if (data_021349c0[2] != e->type2) {
        return;
    }
    e->action++;
    *(u32 *)&e->spriteSettings = (*(u32 *)&e->spriteSettings & ~0xc00) | 0x400;
    data_0212c75c.unk_66 = 0x3f40;
    data_0212c75c.unk_68 = 0x10;
    e->timer = 0x10;
    SoundReq(0x7f);
}
