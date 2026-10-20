#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/g_callees.h"

// Yuka (player and wall checks, module yuka). Address -> name:
//   0x02063fd8 rc_yukaPlMoveCheck, 0x0206402c yukaCheck, 0x0206412c ue_bgcheck, 0x02064214 shita_bgcheck,
//   0x020642fc migi_bgcheck, 0x020643e4 hidari_bgcheck (original names)

typedef struct Vars_Yuka {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 yukaFlags; // bit n: player n was checked and is still pending
} Vars_Yuka;

// Wall probe: cell kind at (dx, dy) from the entity; kinds 0x43 and 0x21 are not walls.
#define BG_PROBE(dx, dy, bit)                                                \
    do {                                                                     \
        s32 probeKind = func_02083ccc(e, dx, dy);                            \
        if (probeKind != 0x43 && probeKind != 0x21) {                        \
            if ((u16)(probeKind - 0x14) > 0xb) {                             \
                e->wallFlags = e->wallFlags | (bit);                         \
            }                                                                \
        }                                                                    \
    } while (0)

ARM int rc_yukaPlMoveCheck(PlayerData *player) {
    if ((((u32)((u8 *)player)[0x8b]) << 25) >> 29) {
        return 1;
    }
    if (player->unk_08 == 0x1ac) {
        return 1;
    }
    if (player->unk_02 != 0 && player->unk_02 != 0x25) {
        return 0;
    }
    return func_020860dc(player->entity) != 0;
}

ARM void yukaCheck(Entity *e) {
    func_02084228(e);
    if (VARS(Vars_Yuka, e)->yukaFlags & 1) {
        if (rc_yukaPlMoveCheck(&data_0212ceb0[0])) {
            func_02083f60(e, data_0212ceb0[0].entity);
        } else {
            VARS(Vars_Yuka, e)->yukaFlags = VARS(Vars_Yuka, e)->yukaFlags ^ 1;
        }
    }
    if (VARS(Vars_Yuka, e)->yukaFlags & 2) {
        if (rc_yukaPlMoveCheck(&data_0212ceb0[1])) {
            func_02083f60(e, data_0212ceb0[1].entity);
        } else {
            VARS(Vars_Yuka, e)->yukaFlags = VARS(Vars_Yuka, e)->yukaFlags ^ 2;
        }
    }
    if (VARS(Vars_Yuka, e)->yukaFlags & 4) {
        if (rc_yukaPlMoveCheck(&data_0212ceb0[2])) {
            func_02083f60(e, data_0212ceb0[2].entity);
        } else {
            VARS(Vars_Yuka, e)->yukaFlags = VARS(Vars_Yuka, e)->yukaFlags ^ 4;
        }
    }
    if (VARS(Vars_Yuka, e)->yukaFlags & 8) {
        if (rc_yukaPlMoveCheck(&data_0212ceb0[3])) {
            func_02083f60(e, data_0212ceb0[3].entity);
        } else {
            VARS(Vars_Yuka, e)->yukaFlags = VARS(Vars_Yuka, e)->yukaFlags ^ 8;
        }
    }
}

ARM void ue_bgcheck(Entity *e) {
    BG_PROBE(-21, -25, 0x2);
    BG_PROBE(-5, -25, 0x2);
    BG_PROBE(4, -25, 0x4);
    BG_PROBE(20, -25, 0x4);
}

ARM void shita_bgcheck(Entity *e) {
    BG_PROBE(-21, 24, 0x20);
    BG_PROBE(-5, 24, 0x20);
    BG_PROBE(4, 24, 0x40);
    BG_PROBE(20, 24, 0x40);
}

ARM void migi_bgcheck(Entity *e) {
    BG_PROBE(24, -21, 0x2000);
    BG_PROBE(24, -5, 0x2000);
    BG_PROBE(24, 4, 0x4000);
    BG_PROBE(24, 20, 0x4000);
}

ARM void hidari_bgcheck(Entity *e) {
    BG_PROBE(-25, -21, 0x200);
    BG_PROBE(-25, -5, 0x200);
    BG_PROBE(-25, 4, 0x400);
    BG_PROBE(-25, 20, 0x400);
}
