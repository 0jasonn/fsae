#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"
#include "game/savemedia.h"

// Set actor unit 9 (module set). Address -> name (original name):
//   0x02057568 SetMove

// File-local fields of the set actors (Entity bytes from 0x7c on).
typedef struct SetMoveVars {
    u8 unk_00[0x7c];
    u32 followFlags; // low 2 bits: player index to follow, bit 7: follow the player
} SetMoveVars;

extern const EntityFunc data_020d85b8[];

ARM void SetMove(Entity *e) {
    Entity *player;

    if (e->action == 0) {
        SetInit(e);
    }
    if (e->iframes != 0) {
        e->iframes++;
    }
    data_020d85b8[e->objId](e);
    if (e->objId == 0xf && e->type == 0x18 && (VARS(SetMoveVars, e)->followFlags & 0x80) != 0) {
        player = data_0212ceb0[VARS(SetMoveVars, e)->followFlags & 3].entity;
        e->x.HALF.HI = player->x.HALF.HI;
        e->y.HALF.HI = player->y.HALF.HI - 0x18;
        e->z.WORD = player->z.WORD;
    }
    func_020857c8(e);
    e->contactFlags &= 0x7f;
}
