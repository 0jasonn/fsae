#include "engine/functions.h"
#include "global.h"

extern "C" {
extern u8 *data_021848b0; // sound state pointer
}

// Each SndState_LookupAt<N> takes the entry index and reads the block at state+0x98. Its table is the block word at
// +N (zero means no table), entries are word offsets from +4, and the result is the block plus the entry offset
// or 0 when the index is out of range or the offset is zero.

// func_020c0650: lookup through the block table at +0xc.
extern "C" u8 *func_020c0650(s32 index);
ARM u8 *func_020c0650(s32 index) {
    u8 *state;
    u8 *table;
    u8 *block;
    u32 offset;

    state = data_021848b0;
    table = *(u8 **)(state + 0x98);
    offset = *(u32 *)(table + 0xc);
    if (offset == 0) {
        table = 0;
    } else {
        table = table + offset;
    }
    if (table == 0) {
        return 0;
    }
    if (index < 0) {
        return 0;
    }
    if ((u32)index >= *(u32 *)table) {
        return 0;
    }
    offset = *(u32 *)(table + index * 4 + 4);
    block = *(u8 **)(state + 0x98);
    if (offset == 0) {
        block = 0;
    } else {
        block = block + offset;
    }
    return block;
}

// SndState_LookupAt10: lookup through the block table at +0x10.
extern "C" u8 *SndState_LookupAt10(s32 index);
ARM u8 *SndState_LookupAt10(s32 index) {
    u8 *state;
    u8 *table;
    u8 *block;
    u32 offset;

    state = data_021848b0;
    table = *(u8 **)(state + 0x98);
    offset = *(u32 *)(table + 0x10);
    if (offset == 0) {
        table = 0;
    } else {
        table = table + offset;
    }
    if (table == 0) {
        return 0;
    }
    if (index < 0) {
        return 0;
    }
    if ((u32)index >= *(u32 *)table) {
        return 0;
    }
    offset = *(u32 *)(table + index * 4 + 4);
    block = *(u8 **)(state + 0x98);
    if (offset == 0) {
        block = 0;
    } else {
        block = block + offset;
    }
    return block;
}

// SndState_LookupAt14: lookup through the block table at +0x14.
extern "C" u8 *SndState_LookupAt14(s32 index);
ARM u8 *SndState_LookupAt14(s32 index) {
    u8 *state;
    u8 *table;
    u8 *block;
    u32 offset;

    state = data_021848b0;
    table = *(u8 **)(state + 0x98);
    offset = *(u32 *)(table + 0x14);
    if (offset == 0) {
        table = 0;
    } else {
        table = table + offset;
    }
    if (table == 0) {
        return 0;
    }
    if (index < 0) {
        return 0;
    }
    if ((u32)index >= *(u32 *)table) {
        return 0;
    }
    offset = *(u32 *)(table + index * 4 + 4);
    block = *(u8 **)(state + 0x98);
    if (offset == 0) {
        block = 0;
    } else {
        block = block + offset;
    }
    return block;
}

// SndState_LookupAt18: lookup through the block table at +0x18.
extern "C" u8 *SndState_LookupAt18(s32 index);
ARM u8 *SndState_LookupAt18(s32 index) {
    u8 *state;
    u8 *table;
    u8 *block;
    u32 offset;

    state = data_021848b0;
    table = *(u8 **)(state + 0x98);
    offset = *(u32 *)(table + 0x18);
    if (offset == 0) {
        table = 0;
    } else {
        table = table + offset;
    }
    if (table == 0) {
        return 0;
    }
    if (index < 0) {
        return 0;
    }
    if ((u32)index >= *(u32 *)table) {
        return 0;
    }
    offset = *(u32 *)(table + index * 4 + 4);
    block = *(u8 **)(state + 0x98);
    if (offset == 0) {
        block = 0;
    } else {
        block = block + offset;
    }
    return block;
}

// SndState_LookupAt1c: lookup through the block table at +0x1c.
extern "C" u8 *SndState_LookupAt1c(s32 index);
ARM u8 *SndState_LookupAt1c(s32 index) {
    u8 *state;
    u8 *table;
    u8 *block;
    u32 offset;

    state = data_021848b0;
    table = *(u8 **)(state + 0x98);
    offset = *(u32 *)(table + 0x1c);
    if (offset == 0) {
        table = 0;
    } else {
        table = table + offset;
    }
    if (table == 0) {
        return 0;
    }
    if (index < 0) {
        return 0;
    }
    if ((u32)index >= *(u32 *)table) {
        return 0;
    }
    offset = *(u32 *)(table + index * 4 + 4);
    block = *(u8 **)(state + 0x98);
    if (offset == 0) {
        block = 0;
    } else {
        block = block + offset;
    }
    return block;
}
