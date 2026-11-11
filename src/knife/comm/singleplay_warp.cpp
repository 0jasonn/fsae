#include "actor/object/warp.h"
#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/comm/singleplay_warp_api.h"

// Moves the partner (player1) next to player0 when the partner is far behind (WarpPartner, 0x02094d08).
// Returns TRUE when the partner was warped.
BOOL Knife_Single_SinglePlay_WarpPartner(void *self, PlayerData *player0, PlayerData *player1) {
    SinglePlayWarpHead *sp = (SinglePlayWarpHead *)self;
    Entity *e0;
    Entity *e1;
    EntityHead saved;
    int cls;
    int kind;
    int zero;

    e0 = player0->entity;
    e1 = player1->entity;
    if ((player0->statusFlags & 0x341) || (player1->statusFlags & 0x341) || player1->unk_0a != 0
        || (player1->hitFlags & 0x40)
        || (e0->action == 3 || e1->action == 3 || e0->action == 0x11 || e1->action == 0x11 || e0->action == 0x12
            || e1->action == 0x12 || e0->action == 6 || e1->action == 6 || player0->motionId == 0x2c1
            || player1->motionId == 0x2c1)
        || (player0->unk_02 != 0 || player1->unk_02 != 0) || (e0->action == 0xf || e1->action == 0xf)
        || (player1->statusFlags & 0x1000) || Knife_Single_SinglePlay_CheckShell(self, e1, 2)) {
        return FALSE;
    }
    zero = 0;
    cls = func_02083d18(e0, zero, 3);
    if (cls == 0x21 || cls == 0x25) {
        kind = func_02083c74(e0, zero, 3);
        if (kind - 0x176 == ((PalBits *)&playerWork[e0->type].paletteBits)->b) {
            return zero;
        }
        if (player0->unk_14 == 0
            || ((sp->playerMask & (1 << sp->contNo)) && !(player1->statusFlags & 0x80))) {
            if (kind != 0x4016 && kind != 0x4017) {
                return FALSE;
            }
        }
    } else if ((u8)(cls + 0xec) <= 1) {
        if (!(player1->statusFlags & 0x80)) {
            return zero;
        }
    }
    saved = *(EntityHead *)e1;
    ObjPosCopy(e0, (Entity *)&saved);
    if (player1->unk_26 == 0) {
        if (Knife_Single_SinglePlay_WarpAtariCheck(self, (Entity *)&saved)) {
            return FALSE;
        }
    }
    ObjPosCopy(e0, e1);
    zero = 0;
    if (player1->unk_0b == 0) {
        e1->animationState = e0->animationState;
    }
    e1->y.HALF.HI += 1;
    KemuriSet(e1);
    e1->y.HALF.HI -= 1;
    sp->unk_05 = zero;
    player1->unk_26 = zero;
    if (player0->unk_26 != 0) {
        player1->statusFlags &= 0xff7f;
    }
    sp->unk_0c = zero;
    e1->unk_42 = zero;
    *(u16 *)&player1->unk_8c[0] = zero;
    *(u16 *)&player1->unk_8c[2] = zero;
    Knife_Single_SinglePlay_InitializeFormation(self);
    return TRUE;
}

// Same as WarpPartner, but moves the partner to the map position (x, y) (WarpPartnerToTarget, 0x02095148).
BOOL Knife_Single_SinglePlay_WarpPartnerToTarget(void *self, PlayerData *player0, PlayerData *player1, s16 x, volatile s16 y) { // volatile: the ROM re-reads y from the stack each time
    SinglePlayWarpHead *sp = (SinglePlayWarpHead *)self;
    Entity *e0;
    Entity *e1;
    EntityHead saved;
    int cls;
    int kind;
    int zero;

    e0 = player0->entity;
    e1 = player1->entity;
    zero = 0;
    if ((player0->statusFlags & 0x341) || (player1->statusFlags & 0x341) || player1->unk_0a != 0
        || (player1->hitFlags & 0x40)
        || (e0->action == 3 || e1->action == 3 || e0->action == 0x11 || e1->action == 0x11 || e0->action == 0x12
            || e1->action == 0x12 || player0->motionId == 0x2c1 || player1->motionId == 0x2c1)) {
        return FALSE;
    }
    cls = func_02083d30(x, y + 3, e0->layer);
    if (cls == 0x21 || cls == 0x25) {
        kind = func_02083c74(e0, zero, 3);
        if (kind != 0x4016 && kind != 0x4017) {
            return zero;
        }
    } else if ((u8)(cls + 0xec) <= 1) {
        if (!(player1->statusFlags & 0x80)) {
            return zero;
        }
    }
    saved = *(EntityHead *)e1;
    ObjPosCopy(e0, (Entity *)&saved);
    *(s16 *)((u8 *)&saved + 0x32) = x;
    *(s16 *)((u8 *)&saved + 0x36) = y;
    if (player1->unk_26 == 0) {
        if (Knife_Single_SinglePlay_WarpAtariCheck(self, (Entity *)&saved)) {
            return FALSE;
        }
    }
    ObjPosCopy(e0, e1);
    e1->x.HALF.HI = x;
    e1->y.HALF.HI = y + 1;
    KemuriSet(e1);
    e1->y.HALF.HI -= 1;
    sp->unk_05 = 0;
    player1->unk_26 = 0;
    if (player0->unk_26 != 0) {
        player1->statusFlags &= 0xff7f;
    }
    sp->unk_0c = 0;
    e1->unk_42 = 0;
    *(u16 *)&player1->unk_8c[0] = 0;
    *(u16 *)&player1->unk_8c[2] = 0;
    Knife_Single_SinglePlay_InitializeFormation(self);
    return TRUE;
}

// Knife::Single::SinglePlay::WarpAtariCheck (0x020954f0): calls the Thumb helper func_0208a06c on the entity, then
// reports whether the four three-bit groups of the entity's wall flags at 0x2c (bits 13-15, 9-11, 5-7 and 1-3) are all set.
// The flags are written back unchanged.

BOOL Knife_Single_SinglePlay_WarpAtariCheck(void *self, Entity *e) {
    u16 saved;
    u16 flags;
    BOOL group1;
    BOOL group2;
    BOOL group3;

    saved = e->wallFlags;
    func_0208a06c(e);
    group3 = group2 = group1 = FALSE;
    flags = e->wallFlags;
    if (flags & 0xe000) {
        if (flags & 0xe00) {
            group3 = TRUE;
        }
    }
    if (group3) {
        if (flags & 0xe0) {
            group2 = TRUE;
        }
    }
    if (group2) {
        if (flags & 0xe) {
            group1 = TRUE;
        }
    }
    e->wallFlags = saved;
    return group1;
}
