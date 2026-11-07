#ifndef WIP_A_RECELL_A_H
#define WIP_A_RECELL_A_H

#include "engine/functions.h"
#include "engine/player.h"

typedef struct MapScroll {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 scrollX;
    /* 1a */ u16 scrollY;
} MapScroll;
extern MapScroll mapState;

extern const u16 *const recell0Cells[]; // recell0Cells, one list of replacement cell ids per block type
extern const u16 *const recell1Cells[]; // recell1Cells

void recell0(Entity *e);
void recell1(Entity *e);

#endif
