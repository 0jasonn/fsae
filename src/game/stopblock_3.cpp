#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/stopblock.h"

// Functions in this file (original names from the debug build):
//   sbKemuriSet

// Places the smoke (kemuri) object at the stop block's cell, in the layer bits of the key
void sbKemuriSet(STOPBLOCK_WORK_ *block) {
    Entity *e;

    e = GetSetWork(0xf, 2, 0);
    if (e == 0) {
        return;
    }
    e->x.HALF.HI = ((((u32)block->key << 26) >> 22)) | 8;
    e->y.HALF.HI = ((block->key & 0xfc0) >> 2) | 8;
    e->layer = block->key & 0xc000;
    func_0208ae78(e);
}

// Stop block (sb) module. 0x0204ec38 sbGarbageCollection (original name)
// Stop block records are 4 bytes; a record with a zero key at offset 0 is free. Compacts the live records towards
// the front: the first free record from the front is filled with the last live record from the back.
void sbGarbageCollection(STOPBLOCK_WORK_ *begin, STOPBLOCK_WORK_ *end) {
    u32 *front;
    u32 *back;

    back = (u32 *)end;
    back--;
    while (*(u16 *)back == 0 && back > (u32 *)begin) {
        back--;
    }
    if ((u32 *)begin >= back) {
        return;
    }
    for (front = (u32 *)begin; front < back; front++) {
        if (*(u16 *)front == 0) {
            *front = *back;
            *back = 0;
            while (*(u16 *)back == 0 && back > front) {
                back--;
            }
        }
    }
}
