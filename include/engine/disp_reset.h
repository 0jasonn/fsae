#ifndef WIP_DISP_RESET_H
#define WIP_DISP_RESET_H

#include "engine/functions.h"
#include "game/dispctrl_api.h"

extern u8 data_0212c4e0;
extern u8 data_0212c4c8;
extern u8 data_0212ccb0[];
extern u32 data_0212c56c;
extern u8 data_0212cdb0[];
extern u32 data_0212c570;
extern u8 data_0212de50[];
extern u32 data_0212c528;
typedef struct DispState {
    u8 unk_00[4];
    u8 unk_04;
    u8 unk_05;
} DispState;
extern DispState data_0212c594;
extern u8 objAffineSet[];
extern u8 data_021361a0[];
extern u8 hblankDma;

#endif
