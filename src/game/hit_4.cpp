#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "game/hitdecls.h"
#include "game/hit.h"

// Field of the player slot at byte offset `off` of playerWork (the slot is selected by the entity type)
#define PLAYER_FIELD(type, field, off) (*(type *)((u8 *)&playerWork[0].field + (off)))

// Rupee-like hit (hit handler table entry): when the rupee can be taken (the slot is neither busy nor flagged), the slot's
// flags are set, e is placed at t and takes over its sprite bits.
BOOL hit_rupeelike(Entity *e, Entity *t, u8 unused) {
    s32 off;
    u16 bits;

    if (func_020860dc(e) != 0) {
        off = e->type * sizeof(PlayerData);
        if ((PLAYER_FIELD(u16, statusFlags, off) & 0x81) == 0 && PLAYER_FIELD(u8, unk_26, off) == 0) {
            PLAYER_FIELD(u8, unk_1a, off) |= 0x80;
            PLAYER_FIELD(u8, unk_0a, off) |= 0x80;
            bits = PLAYER_FIELD(u16, statusFlags, off);
            bits |= 0x10;
            PLAYER_FIELD(u16, statusFlags, off) = bits;
            PLAYER_FIELD(u8, unk_02, off) = 0;
            ObjPosCopyOfs32(t, e, 0, 1);
            e->spriteSettings.b14 = t->spriteSettings.b14;
            e->spriteSettings.b30 = t->spriteSettings.b30;
            e->iframes = 0xff;
            t->iframes = 0xf8;
            return 1;
        }
    }
    return 0;
}
