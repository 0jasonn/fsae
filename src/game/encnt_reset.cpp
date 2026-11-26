#include "engine/functions.h"
#include "actor/enemy/encnt.h"
#include "actor/enemy/em29.h"
#include "game/encnt.h"

// Encnt_Reset (0x0204363c, called by makemap_30): clears the encounter state and picks a random encounter record from
// the row of data_020f270c that belongs to the difficulty (mode 2) or the level, then copies the record's fields.
// The record assignment is written in both branches (the compiler merges the tails); with one assignment after the
// if/else the stored pointer is forwarded and the index multiply becomes smulbb instead of the ROM's mla + reload.
void Encnt_Reset(void) {
    MemClearFast(&encntState, 0x68);
    encntState.state = 0;
    encntSharedState[0] = 0;
    if (gameState.unk_01 == 2) {
        encntState.record = &data_020f273c[data_020f270c[(gameState.difficulty + 3) * 8 + (Random() & 7)]];
    } else {
        encntState.record = &data_020f273c[data_020f270c[(gameState.level - 1) * 8 + (Random() & 7)]];
    }
    encntState.timerBase = encntState.record->a;
    encntState.recB = encntState.record->b;
    encntState.recC = encntState.record->c;
    encntState.recD = encntState.record->d;
    encntState.recE = encntState.record->e;
    encntState.timerRange = encntState.record->f;
    encntState.recG = encntState.record->g;
}
