#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build, plain in the ROM):
//   getResourceData (0x020ac3d0), getResourceSize (0x020ac40c)

// The subtask data helpers (C++ linkage, see src/game/subtask_data.cpp and subtask_data_0.cpp)
s32 _get_subtask_data(s32 index);
s32 _get_subtask_data_lang(s32 index);
s32 _get_subtask_data_size(s32 index);
s32 _get_subtask_data_size_lang(s32 index);

extern u8 data_0212c55c[]; // pointer to the table of the subtask data (non-language entries)
extern u8 data_0212c560[]; // pointer to the table of the subtask data (language entries)

// getResourceData(unsigned long, unsigned char) (0x020ac3d0): pointer to the entry in the table
extern "C" void *getResourceData(u32 id, u8 lang);
ARM void *getResourceData(u32 id, u8 lang) {
    if (lang != 0) {
        return (u8 *)*(u32 *)data_0212c560 + _get_subtask_data_lang(id);
    }
    return (u8 *)*(u32 *)data_0212c55c + _get_subtask_data(id);
}

// getResourceSize(unsigned long, unsigned char) (0x020ac40c): size of the entry, language table when lang is set
extern "C" s32 getResourceSize(u32 id, u8 lang);
ARM s32 getResourceSize(u32 id, u8 lang) {
    if (lang != 0) {
        return _get_subtask_data_size_lang(id);
    }
    return _get_subtask_data_size(id);
}
