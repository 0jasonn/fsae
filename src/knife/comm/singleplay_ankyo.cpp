#include "engine/functions.h"
#include "knife/comm/singleplay_ankyo.h"

// Knife::Single::SinglePlay::CheckAnkyo (0x02094a88 and 0x02094b08): TRUE when the map value under a position (cell kinds
// 0x21 and 0x25 only) is not the player's own palette index (value 0x176 + palette) and not one of the two values after
// 0xbfea (0x15 and 0x16 as a halfword), i.e. when the position holds another player's dark marker.

// CheckAnkyo(unsigned char, OBJ_WORK_*, short, short) (0x02094a88)
BOOL Knife_Single_SinglePlay_CheckAnkyo_094a88(void *self, u8 kind, Entity *e, s16 x, s16 y) {
    if (kind != 0x21 && kind != 0x25) {
        return FALSE;
    }
    s32 value = func_02083c8c(x, y, e->layer);
    if (value - 0x176 == ((PalBits *)&playerWork[e->type].paletteBits)->b || (u16)(value + 0xbfea) <= 1) {
        return FALSE;
    }
    return TRUE;
}

// CheckAnkyo(PL_WORK_*) (0x02094b08): the same test for the position stored in the player
BOOL Knife_Single_SinglePlay_CheckAnkyo_094b08(void *self, PlayerData *player) {
    if (player->unk_12 != 4 && player->unk_12 != 0x94) {
        return FALSE;
    }
    u16 value = player->unk_24;
    if (value - 0x176 == ((PalBits *)&player->paletteBits)->b || (u16)(value + 0xbfea) <= 1) {
        return FALSE;
    }
    return TRUE;
}
