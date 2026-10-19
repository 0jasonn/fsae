#include "engine/functions.h"
#include "global.h"
#include "engine/misc_d.h"

// data_02134980 is the pause state block: [0] phase, [1] chosen pause option, [2] delay timer,
// [0xe] reset flag, [0xf] set when the wireless session is being closed

extern u8 data_02134980[];
extern u16 data_021355a0;
extern u16 data_0212c58c[];
extern u8 data_0212c4b8;
extern u8 data_0212c4d4;
extern u16 data_0212c520;


#include "game/pl.h"

#define PL_ARR (*(PlWork (*)[4])data_0212ceb0)

extern u16 data_0212c574[];
extern u8 data_0212dd90[];
extern u8 data_0212e190[];
extern u8 data_0212c4e4;
extern u16 data_0212c514;
extern u16 data_0212c510;
extern Entity *data_0212c534;
extern u16 data_0212c584[];
extern u8 data_0212c868[];
extern const EntityFunc data_02115258[];


extern u8 data_0217d36c[];
extern const u32 data_021186e4[];
extern const u8 data_0212c84c[];

extern const s8 *const data_0211525c[];

extern const VoidFunc data_02115268[];
extern u8 data_0212c504;



ARM void PlWeaponFireCheck(Entity *e) {
    s32 contact;
    Entity *target;
    Entity *shot;
    s32 dy;
    s32 dx;

    contact = e->contactFlags;
    if (!(contact & 0x80)) {
        return;
    }
    contact &= 0x7f;
    if (contact == 0xc) {
        return;
    }
    if (contact < 4 || contact > 0x15) {
        return;
    }
    e->contactedEntity->contactFlags = (e->contactedEntity->contactFlags & 0x7f) | 0x40;
    e->unk_3f = 0xe;
    e->contactedEntity->unk_3f = 0xe;
    dx = e->x.WORD - e->contactedEntity->x.WORD;
    dy = e->y.WORD - e->contactedEntity->y.WORD;
    shot = GetObjWork();
    if (shot == 0) {
        return;
    }
    shot->unk_09 = 0x17;
    shot->unk_08 = 6;
    shot->x.WORD = e->x.WORD - (dx >> 1);
    shot->y.WORD = e->y.WORD - (dy >> 1);
    shot->spriteSettings.b14 = e->spriteSettings.b14;
    shot->spriteSettings.b30 = e->spriteSettings.b30;
    shot->unk_50 = e->unk_50;
    RegistObjWork(6, shot);
}

ARM void PlayerTrans(void) {
    s32 i;

    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        PL_ARR[i].entity->y.HALF.HI += PL_ARR[i].yOffset;
        if ((u8)(PL_ARR[i].state + 0xfd) <= 1) {
            if (*(Entity **)&PL_ARR[i].entity->unk_6c[0] != 0 && (*(Entity **)&PL_ARR[i].entity->unk_6c[0])->child != 0) {
                PlLiftSync(PL_ARR[i].entity);
            }
        }
        if (PL_ARR[i].unk_36 & 4) {
            func_0208a95c(PL_ARR[i].entity);
        }
        if (PL_ARR[i].weapon != 0) {
            PlWeaponSync(PL_ARR[i].entity, PL_ARR[i].weapon);
        }
    }
}
