#ifndef WIP_B_RANDOMSET_H
#define WIP_B_RANDOMSET_H

#include "engine/functions.h"
#include "game/srchcells_api.h"

// Random set records (0x0c bytes each, eight of them at data_02134ae8). src/game/randomset.cpp clears them in
// RandomSetInit; GetCellsInRandomSet searches and fills them. The reviewer should use this one shared type.
typedef struct RandomSetWork {
    /* 00 */ u16 *cells;  // block returned by srchCells; NULL marks a free record
    /* 04 */ u16 cell;    // start cell the block was searched from
    /* 06 */ u8 width;
    /* 07 */ u8 height;
    /* 08 */ u16 unk_08;  // set to 0 when the record is filled
} RandomSetWork;

extern RandomSetWork data_02134ae8[8];

// original zFree(void*), C++ linkage (_Z5zFreePv)
void zFree(void *p);

#endif
