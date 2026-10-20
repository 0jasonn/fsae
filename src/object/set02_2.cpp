#include "engine/functions.h"
#include "global.h"

// Set02 actor, second unit (module set02). Address -> name:
//   0x0205a1b0 set02_move (original name)

// data_0212c75c as read by set02_move: scroll origins used to place the actor on screen.
typedef struct Set02Screen {
    /* 00 */ u8 unk_00[0x0a];
    /* 0a */ u16 altScrollX; // origin for type 1
    /* 0c */ u16 altScrollY;
    /* 0e */ u8 unk_0e[8];
    /* 16 */ u16 scrollX; // origin for type 0
    /* 18 */ u16 scrollY;
} Set02Screen;

extern Set02Screen data_0212c75c;
extern u8 data_021348d8;   // flag, nonzero: the actor is placed low and does not get the x offset
extern u8 data_021349c0[]; // byte 0x14: nonzero when the actor should be put back into the work list
extern const s8 data_0211565c[]; // vertical bob table, indexed by timer & 0xf
extern u16 data_0212c594;  // frame counter, the bob timer advances when its low 5 bits are zero

ARM void set02_move(Entity *e) {
    switch (e->type) {
    case 0:
        e->x.HALF.HI = 0x58 - data_0212c75c.scrollX;
        e->y.HALF.HI = 0x3c - data_0212c75c.scrollY;
        if (data_021349c0[0x14] != 0) {
            PutObjWork(e);
        }
        break;
    case 1:
        e->x.HALF.HI = 0x58 - data_0212c75c.altScrollX;
        e->y.HALF.HI = 0x3c - data_0212c75c.altScrollY;
        if (data_021348d8 == 0) {
            e->x.HALF.HI += 3;
        }
        if (data_021349c0[0x14] != 0) {
            PutObjWork(e);
        }
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        MoveDir(e);
        if (e->x.HALF.HI > 0x130) {
            e->x.HALF.HI = -0x40;
        }
        break;
    case 7:
        MoveDir(e);
        if (e->x.HALF.HI > 0x180) {
            e->x.HALF.HI = -0x80;
        }
        break;
    case 8:
    case 9:
        UpdateAnimationSingleFrame(e);
        MoveDir(e);
        if (e->x.HALF.HI > 0x100) {
            e->x.HALF.HI = -(Random() & 0x3f) - 0x10;
            e->y.HALF.HI = (Random() & 0x1f) + 0x70;
            e->subtimer = e->y.HALF.HI;
            e->speed = (Random() & 0xf) + 0x20;
            e->unk_16 = 0;
            e->spriteSettings.b0 = 2;
            e->timer = Random() & 0xf;
            InitAnimationForceUpdate(e, e->type);
        }
        if (e->unk_16 == 0) {
            if ((Random() & 0x3ff) == 0xd) {
                InitAnimationForceUpdate(e, 0x15);
                e->unk_16 = 1;
            }
        } else if (e->frame == 0x80) {
            e->spriteSettings.b0 = 0;
            e->x.HALF.HI = 0x100;
        }
        e->y.HALF.HI = e->subtimer + data_0211565c[e->timer & 0xf];
        if ((data_0212c594 & 0x1f) == 0) {
            e->timer++;
        }
        break;
    case 22:
        if (data_021348d8 != 0) {
            e->y.HALF.HI = 9;
        }
        if (data_021349c0[0x14] != 0) {
            PutObjWork(e);
        }
        break;
    }
}
