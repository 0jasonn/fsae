#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

// Lever movement of the nemoto family (module nemoto). Address -> name:
//   0x0206c1c8 nemoto_leverMove (original leverMove)
// Calls nemoto_setdist (0x0206c328, nemoto_2.cpp).

extern const s16 trigTable[];        // sine table, sin at [dir * 8], cos at [dir * 8 + 0x40]
extern const u8 data_020daa0f[];     // direction index per e->type (data_020daa0f)
void nemoto_setdist(Entity *e);

typedef struct Vars_NemotoLever {
    /* 00 */ u8 unk_00[0x72];
    /* 72 */ u16 holdTimer;    // set to 0x258 when no wireless session is active
    /* 74 */ u8 unk_74[2];
    /* 76 */ u16 progress;     // compared with target
    /* 78 */ u8 unk_78[4];
    /* 7c */ u16 target;
} Vars_NemotoLever;

ARM void nemoto_leverMove(Entity *e) {
    Vars_NemotoLever *v = VARS(Vars_NemotoLever, e);
    Entity *player;
    u8 dir;
    s16 oldX;
    s16 oldY;
    s16 delta;
    s16 step;
    s32 sinValue;
    s32 cosValue;

    player = data_0212ceb0[e->type2].entity;
    dir = data_020daa0f[e->type];
    if (v->progress > v->target) {
        oldX = player->x.HALF.HI;
        oldY = player->y.HALF.HI;
        func_020852f8(player, e->speed, dir);
        if (oldX != player->x.HALF.HI || oldY != player->y.HALF.HI) {
            switch (e->type) {
            case 0:
                delta = player->y.HALF.HI - oldY;
                break;
            case 1:
                delta = oldX - player->x.HALF.HI;
                break;
            case 2:
                delta = oldY - player->y.HALF.HI;
                break;
            case 3:
                delta = player->x.HALF.HI - oldX;
                break;
            }
            step = delta << 8;
            sinValue = trigTable[dir * 8];
            cosValue = trigTable[dir * 8 + 0x40];
            e->x.WORD += step * sinValue;
            e->y.WORD -= step * cosValue;
            nemoto_setdist(e);
            if (v->progress <= v->target) {
                EnqueueSFX(0x12);
            } else {
                e->subtimer--;
                if (e->subtimer == 0) {
                    e->subtimer = 8;
                    EnqueueSFX(0x8b);
                }
            }
        }
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        v->holdTimer = 0x258;
    }
}
