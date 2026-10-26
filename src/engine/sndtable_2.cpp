#include "engine/functions.h"
#include "global.h"
#include "engine/sndrecord.h"

extern "C" {
extern u8 *data_021848b0; // sound state pointer
void *SndHeap_InitLinear(void *base, u32 size, s32 flags);
void Menu_ForwardC28b0(void *heap);
}

// SndTable_GetWord14: the word at +0x14 of entry index of the table at state+0x90 (0 when index is out of range).
extern "C" u32 SndTable_GetWord14(s32 index);
ARM u32 SndTable_GetWord14(s32 index) {
    u8 *table;

    table = *(u8 **)(data_021848b0 + 0x90);
    if ((u32)index >= *(u32 *)(table + 8)) {
        return 0;
    }
    return *(u32 *)(table + index * 16 + 0x14);
}

// SndTable_SetWord14: sets the word at +0x14 of entry index of the table at state+0x90 (no range check).
extern "C" void SndTable_SetWord14(s32 index, u32 value);
ARM void SndTable_SetWord14(s32 index, u32 value) {
    u8 *table;

    table = *(u8 **)(data_021848b0 + 0x90);
    *(u32 *)(table + index * 16 + 0x14) = value;
}
