#ifndef WIP_F_SET3D_H
#define WIP_F_SET3D_H

// Prototypes used by src/wip/F/set3d.cpp that engine/functions.h does not declare yet (to be moved there).
#include "engine/functions.h"

void set3dyure(Entity *e);     // 0x0205d940, original name set3dyure(OBJ_WORK_*)
Entity *settail(Entity *e); // 0x0205d8e4, original name settail(OBJ_WORK_*), returns the child it creates

typedef struct Vars_Set3d {
    /* 00 */ u8 unk_00[0x1c];
    /* 1c */ u32 settingsWord; // sprite settings word, bit 2 is set by set3dyure
    /* 20 */ u8 unk_20[0x64 - 0x20];
    /* 64 */ u16 timer64;
    /* 66 */ u8 unk_66[2];
    /* 68 */ u32 waitCount;
} Vars_Set3d;

#endif
