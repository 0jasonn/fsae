#include "engine/functions.h"
#include "global.h"
#include "engine/irq.h"
#include "engine/display_state.h"

// Set02 actor, second unit (module set02). Address -> name:
//   0x0205a1b0 set02_move (original name)

extern u8 data_021348d8;   // flag, nonzero: the actor is placed low and does not get the x offset
#include "engine/effect_state.h"
extern const s8 data_0211565c[]; // vertical bob table, indexed by timer & 0xf

void set02_move(Entity *e) {
    switch (e->type) {
    case 0:
        e->x.HALF.HI = 0x58 - displayState.bg[1].scrollX;
        e->y.HALF.HI = 0x3c - displayState.bg[1].scrollY;
        if (effectState.restoreFlag != 0) {
            PutObjWork(e);
        }
        break;
    case 1:
        e->x.HALF.HI = 0x58 - displayState.bg[0].scrollX;
        e->y.HALF.HI = 0x3c - displayState.bg[0].scrollY;
        if (data_021348d8 == 0) {
            e->x.HALF.HI += 3;
        }
        if (effectState.restoreFlag != 0) {
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
        if ((frameState.frameCount & 0x1f) == 0) {
            e->timer++;
        }
        break;
    case 22:
        if (data_021348d8 != 0) {
            e->y.HALF.HI = 9;
        }
        if (effectState.restoreFlag != 0) {
            PutObjWork(e);
        }
        break;
    }
}
