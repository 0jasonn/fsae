#include "engine/functions.h"
#include "global.h"

extern "C" u8 data_02186fd0[];

// ObjEntry_Get (provisional name): the 0x30-byte entry at index in the table whose base pointer is at +8 of data_02186fd0.
extern "C" u8 *ObjEntry_Get(u32 index);
ARM u8 *ObjEntry_Get(u32 index) {
    return *(u8 **)(data_02186fd0 + 8) + index * 0x30;
}

// ObjEntry_Setup (provisional name): the entry at index gets -1 at +0x24 and the words a and b at +0x28 and +0x2c.
extern "C" void ObjEntry_Setup(u32 index, u32 a, u32 b);
ARM void ObjEntry_Setup(u32 index, u32 a, u32 b) {
    u8 *entry;

    entry = ObjEntry_Get(index);
    *(s32 *)(entry + 0x24) = -1;
    *(u32 *)(entry + 0x28) = a;
    *(u32 *)(entry + 0x2c) = b;
}

