#include "engine/functions.h"
#include "engine/player.h"
#include "game/bganm_api.h"
#include "engine/bg_buff.h"

extern const s16 cellDeltaTable[]; // cell step per direction, indexed by direction >> 3
extern u16 data_0213493c[4]; // cell of the block each player is pushing (0xffff none)

// setmoveblock (0x02023608): player e pushes a block from the cell `cell` in direction `mode`. If the cell it moves to
// is free (or a floor-like cell), no other player pushes that cell and a free object exists, an object of kind 6, id 7
// is registered at the cell, the player enters push state 5 and the target cell is reserved.
void setmoveblock(Entity *e, u16 cell, u8 mode) {
    int target = cell + cellDeltaTable[mode >> 3];
    u32 i;
    BG_BUFF_ *buffer;
    Entity *block;
    u8 attr;

    if (Check1BlockOshiYoyaku(target, e->layer) != 0) {
        return;
    }
    buffer = (BG_BUFF_ *)GetBgBuffAdrs(e->layer);
    attr = buffer->attr[target];
    if (attr != 0 && (u8)(attr - 0x20) >= 0x10) {
        return;
    }
    for (i = 0; i < 4; i++) {
        if (cell == data_0213493c[i]) {
            return;
        }
    }
    block = GetObjWork();
    if (block == NULL) {
        return;
    }
    block->objKind = 6;
    block->objId = 7;
    block->type = 0;
    block->direction = mode;
    block->x.HALF.HI = ((cell & 0x3f) << 4) + 8;
    block->y.HALF.HI = ((cell & 0xfc0) >> 2) + 8;
    block->layer = e->layer;
    RegistObjWork(6, block);
    playerWork[e->type].unk_06 = 0xa0;
    playerWork[e->type].state = 5;
    playerWork[e->type].statusFlags |= 1;
    e->x.HALF.LO = 0;
    e->y.HALF.LO = 0;
    e->direction = mode;
    Set1BlockOshiYoyaku(target, e->layer);
    data_0213493c[e->type] = cell;
}
