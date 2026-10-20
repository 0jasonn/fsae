#ifndef WIP_A_NEMOTO_3_H
#define WIP_A_NEMOTO_3_H

#include "engine/functions.h"
#include "object/cellcalls.h"

// Actor fields written by nemoto_writecell (file-local overlay, read by the Set44 family too).
typedef struct Vars_NemotoCell {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u16 cellValue; // result of func_0208367c, written back by nemoto_rewritecell
    /* 7a */ u8 cellFlag;   // result of func_02083d4c, passed to func_0208365c
    /* 7b */ u8 unk_7b;
    /* 7c */ u16 cell;      // map cell index of the actor, from its position and the grid origin
} Vars_NemotoCell;

void nemoto_writecell(Entity *e);
void nemoto_rewritecell(Entity *e);

#endif
