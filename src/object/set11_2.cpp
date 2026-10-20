#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/g_callees.h"

// Set11 actor, second unit (module set11). Address -> name:
//   0x02063678 set11_move, 0x020637c8 set11_break (original names)

extern u16 scrollArgs[];                 // scale x, scale y, rotation for ObjAffineSet2
extern const s16 set11_scaleTable[];     // (x, y) pairs indexed by subtimer, was set11_scaleTable
extern u8 data_0212cebf[];               // byte of the player table, stride 0x94

ARM void set11_move(Entity *e) {
    Entity *other;
    u8 index;

    if (e->contactFlags & 0x80) {
        if (!(e->statusFlags & 0x80)) {
            e->action++;
            e->unk_5e.b0 = 3;
            func_02085d34(e);
            InitAnimationForceUpdate(e, 1);
            EnqueueSFX(0x56);
            return;
        }
        other = e->contactedEntity;
        if (other != NULL && other->objKind == 1) {
            s32 offset = other->type * 0x94;
            u8 *player = (u8 *)data_0212ceb0 + offset;
            if ((((u32)player[0x8b] << 25) >> 29) != 0 && data_0212cebf[offset] == 0) {
                goto timer_step;
            }
        }
        EnqueueSFX(0x5b);
        e->timer = 0x40;
    }

timer_step:
    if (e->timer == 0) {
        return;
    }
    e->timer = e->timer - 1;
    e->subtimer = e->subtimer + 1;
    if (e->timer != 0) {
        index = e->subtimer & 0xe;
        scrollArgs[0] = set11_scaleTable[index];
        scrollArgs[1] = set11_scaleTable[index + 1];
        scrollArgs[2] = 0;
        ObjAffineSet2((const KnifeObjAffineSrcData *)scrollArgs, e);
    } else {
        scrollArgs[0] = 0x100;
        scrollArgs[1] = 0x100;
        scrollArgs[2] = 0;
        ObjAffineSet2((const KnifeObjAffineSrcData *)scrollArgs, e);
    }
}

ARM void set11_break(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        func_020841b0(e);
        PutObjWork(e);
    }
}
