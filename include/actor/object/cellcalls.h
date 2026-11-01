#ifndef WIP_A_CELLCALLS_H
#define WIP_A_CELLCALLS_H

#include "engine/functions.h"

// Map-cell helpers called by the Set44 family and nemoto_writecell (dsd names, no original names yet).
// func_0208365c is unmangled in the original (extern "C"); the others are C++ functions.
extern "C" {
void func_0208365c(s32 mode, u16 cell, u16 layer);
int func_020862a8(Entity *e);
void func_02089988(void *player);
}
void func_0208366c(s32 mode, u16 cell, u16 layer);
u16 func_0208367c(u16 cell, u16 layer);
int func_02085ccc(Entity *e);

// Grid origin used to turn world positions into map cells (data_0212c648, same bytes as UnkStruct_0212c648 in enemy/em09.h).
typedef struct CellOrigin {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 originX;
    /* 1a */ u16 originY;
} CellOrigin;
extern CellOrigin data_0212c648;

#endif
