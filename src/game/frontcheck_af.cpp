#include "engine/functions.h"
#include "global.h"
#include "game/frontcheck_af.h"

// FrontCheckAF (0x020233f0): works out the map cell in front of the actor (its position plus the offset pair for its
// facing) and asks the kind of that cell. For kinds 0x27..0x29 (when the player is in special state 1) and for kind 0x3d
// (when the animation has a frame and the player is not flagged) it adds a record to data_02134bb0. Returns TRUE only
// for kind 0x3d.
BOOL FrontCheckAF(Entity *e, PlayerData *player) {
    u16 cell;
    int kind;
    u32 pairIndex;
    u8 count;
    u32 word;
    const s16 *offset;

    GetBgBuffAdrs(e->layer);
    pairIndex = e->animationState & 6;
    offset = &data_020cd704[pairIndex];
    cell = (u16)(((e->x.HALF.HI + offset[0] - mapState.originX) >> 4) |
                 (((e->y.HALF.HI + offset[1] - mapState.originY) >> 4) << 6));
    kind = func_02083e54(GetCellKind(cell, e->layer));
    switch (kind) {
    case 0x3d:
        if ((player->unk_35 & 0x80) == 0) {
            if (e->frame != 0) {
                count = data_021348e4;
                if (count < 0x10) {
                    u32 *record;
                    word = (cell & 0xfff) | ((((player->unk_35 & 6) << 16) | 0x1000000) | (e->layer & 0xc000));
                    record = &data_02134bb0[count * 2];
                    record[0] = word;
                    record[1] = (u32)e;
                    data_021348e4 = count + 1;
                }
                return TRUE;
            }
        }
        break;
    case 0x27:
    case 0x28:
    case 0x29:
        if (player->specialState == 1) {
            count = data_021348e4;
            if (count < 0x10) {
                u32 *record;
                word = (cell & 0xfff) | ((((e->animationState & 6) << 16) | 0x2000000) | (e->layer & 0xc000));
                record = &data_02134bb0[count * 2];
                record[0] = word;
                record[1] = (u32)e;
                data_021348e4 = count + 1;
            }
        }
        break;
    }
    return FALSE;
}
