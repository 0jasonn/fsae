#include "engine/functions.h"
#include "global.h"
#include "engine/bg_buff.h"
#include "types.h"
#include "engine/a_decls.h"

// Beam (module beam). Original names from the debug build: beam_move.

// Beam-only fields that Entity does not name (file-local overlay on unk_64).
typedef struct Vars_Beam {
    u8 unk_00[0x64];
    s32 lifetime; // 0x64: counts down each frame; the beam is removed at 0
} Vars_Beam;

// Beam move: counts the lifetime down, moves, and removes the beam when it hits a wall, a target or the time runs out.
void beam_move(Entity *e) {
    s32 lifetimeBefore;
    BG_BUFF_ *bg;
    s32 cell;
    u16 flags;
    u16 index;
    u16 value;

    lifetimeBefore = VARS(Vars_Beam, e)->lifetime;
    VARS(Vars_Beam, e)->lifetime = lifetimeBefore - 1;
    if (lifetimeBefore != 0) {
        UpdateAnimationSingleFrame(e);
        MoveDir(e);
        e->timer++;
        if (e->type2 == 0) {
            func_02086168(e);
        }
        PlWeaponFireCheck(e);

        bg = (BG_BUFF_ *)GetBgBuffAdrs(e->layer);
        cell = ((e->x.HALF.HI - mapState.originX) >> 4) | (((e->y.HALF.HI - mapState.originY) >> 4) << 6);
        flags = bg->screen[cell];
        index = (u16)(flags & 0x7ff);
        value = bg->cellMap[index];
        if (func_020899bc(value, data_021180a8) == 0) {
            if (func_02083cdc(e) != 0x47) {
                if (func_02085890(e, data_0211857c, e->x.HALF.HI, e->y.HALF.HI) != 0) {
                    func_020841b0(e);
                    EffectSet(e, 0x19, 0);
                    PutObjWork(e);
                }
            }
        }
        if (e->contactFlags != 0) {
            func_020841b0(e);
            EffectSet(e, 0x19, 0);
            PutObjWork(e);
        }
        if (func_02089e28(e, 0xc) != 0) {
            func_020841b0(e);
            PutObjWork(e);
        }
    } else {
        func_020841b0(e);
        PutObjWork(e);
    }
}
