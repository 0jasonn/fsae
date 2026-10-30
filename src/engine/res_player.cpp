#include "engine/functions.h"
#include "global.h"

extern "C" u32 ResRef_GetWord(u8 *ref);
extern "C" u8 *ResTable_GetEntryAt(u8 *table, u32 index);
extern "C" s32 func_020c323c(u8 *cursor);
extern "C" s32 ResCursor_SeekAndReset(u8 *cursor, u32 index);
extern "C" s32 ResCursor_SetTableAndInit(u8 *cursor, u8 *table);
extern "C" void ResPlayer_Init(u8 *player);
extern "C" void ObjEntry_Setup(u32 index, u32 a, u32 b);

// ResDraw_SetSize (provisional name): stores the two halfwords at +0xc/+0xe and sets flag 8 at +0x12 when the state at +0 is 1.
extern "C" void ResDraw_SetSize(u8 *draw, s32 width, s32 height);
ARM void ResDraw_SetSize(u8 *draw, s32 width, s32 height) {
    u16 flags;

    if (*(u32 *)draw == 1) {
        flags = *(u16 *)(draw + 0x12);
        *(u16 *)(draw + 0xc) = (u16)width;
        *(u16 *)(draw + 0xe) = (u16)height;
        *(u16 *)(draw + 0x12) = (u16)(flags | 8);
    }
}

// ResDraw_SetPriority (provisional name): stores the halfword at +0x10 and sets flag 4 at +0x12 when the state at +0 is 1.
extern "C" void ResDraw_SetPriority(u8 *draw, u32 value);
ARM void ResDraw_SetPriority(u8 *draw, u32 value) {
    u16 flags;

    if (*(u32 *)draw == 1) {
        flags = *(u16 *)(draw + 0x12);
        *(u16 *)(draw + 0x10) = (u16)value;
        *(u16 *)(draw + 0x12) = (u16)(flags | 4);
    }
}

// ResDraw_SetPos (provisional name): stores the words at +4 and +8 and sets flag 2 at +0x12 when the state at +0 is 1.
extern "C" void ResDraw_SetPos(u8 *draw, u32 x, u32 y);
ARM void ResDraw_SetPos(u8 *draw, u32 x, u32 y) {
    u16 flags;

    if (*(u32 *)draw == 1) {
        flags = *(u16 *)(draw + 0x12);
        *(u32 *)(draw + 4) = x;
        *(u32 *)(draw + 8) = y;
        *(u16 *)(draw + 0x12) = (u16)(flags | 2);
    }
}

// ResDraw_Reset is defined below ResDraw_SetModeAndReset.
extern "C" void ResDraw_Reset(u8 *draw);

// ResDraw_SetModeAndReset (provisional name): stores the state at +0 and resets the draw record.
extern "C" void ResDraw_SetModeAndReset(u8 *draw, u32 mode);
ARM void ResDraw_SetModeAndReset(u8 *draw, u32 mode) {
    *(u32 *)draw = mode;
    ResDraw_Reset(draw);
}

// ResDraw_Reset (provisional name): clears the 0x18 bytes from +4 and sets the two words at +4 and +8 to 0x1000.
extern "C" void ResDraw_Reset(u8 *draw);
ARM void ResDraw_Reset(u8 *draw) {
    MIi_CpuClear16(0, draw + 4, 0x18);
    *(u32 *)(draw + 4) = 0x1000;
    *(u32 *)(draw + 8) = 0x1000;
}

// ResPlayer_Refresh (provisional name): when the count at the record of +4 is non-zero, takes the entry from the cursor
// (ResRef_GetWord), stores the table lookup at +0x30, sets the draw state from the entry according to the mode of the
// current record at +0x1c, and, when the table has a sub table and the slot at +0x38 is valid, runs ObjEntry_Setup.
extern "C" void ResPlayer_Refresh(u8 *player);
ARM void ResPlayer_Refresh(u8 *player) {
    u8 *entry;
    u8 *table;
    u8 mode;
    u8 *draw;
    u8 *base;
    u32 *pair;
    u8 *subTable;
    u32 hasSub;
    u32 hasSlot;

    if (*(u16 *)(*(u8 **)(player + 4) + 4) == 0) {
        return;
    }
    entry = (u8 *)ResRef_GetWord(player);
    table = *(u8 **)(player + 0x34);
    *(u8 **)(player + 0x30) = ResTable_GetEntryAt(table, *(u16 *)entry);
    mode = (u8)*(u32 *)(*(u8 **)(player + 0x1c) + 4);
    draw = player + 0x3c;
    ResDraw_SetModeAndReset(draw, 1);
    if (mode != 0) {
        if (mode == 2) {
            ResDraw_SetSize(draw, *(s16 *)(entry + 4), *(s16 *)(entry + 6));
        } else {
            ResDraw_SetPos(draw, *(u32 *)(entry + 4), *(u32 *)(entry + 8));
            ResDraw_SetPriority(draw, *(u16 *)(entry + 2));
            ResDraw_SetSize(draw, *(s16 *)(entry + 0xc), *(s16 *)(entry + 0xe));
        }
    }
    subTable = *(u8 **)(table + 0xc);
    hasSub = (subTable != 0);
    if (hasSub == 0) {
        return;
    }
    hasSlot = (*(s32 *)(player + 0x38) != -1);
    if (hasSlot == 0) {
        return;
    }
    base = *(u8 **)(subTable + 4);
    pair = (u32 *)(base + *(u16 *)entry * 8);
    ObjEntry_Setup(*(u32 *)(player + 0x38), pair[0], pair[1]);
}

// ResPlayer_SetCursorTableAndRefresh is defined below ResPlayer_Start.
extern "C" void ResPlayer_SetCursorTableAndRefresh(u8 *player, u8 *cursorTable);

// ResPlayer_Start (provisional name): stores the entry table at +0x34, the slot -1 at +0x38, sets the draw mode to 1,
// initialises the player and sets the cursor table and refreshes.
extern "C" void ResPlayer_Start(u8 *player, u8 *cursorTable, u8 *entryTable);
ARM void ResPlayer_Start(u8 *player, u8 *cursorTable, u8 *entryTable) {
    *(u8 **)(player + 0x34) = entryTable;
    *(s32 *)(player + 0x38) = -1;
    ResDraw_SetModeAndReset(player + 0x3c, 1);
    ResPlayer_Init(player);
    ResPlayer_SetCursorTableAndRefresh(player, cursorTable);
}

// ResPlayer_SetCursorTableAndRefresh (provisional name): ResCursor_SetTableAndInit on the player, then ResPlayer_Refresh.
extern "C" void ResPlayer_SetCursorTableAndRefresh(u8 *player, u8 *cursorTable);
ARM void ResPlayer_SetCursorTableAndRefresh(u8 *player, u8 *cursorTable) {
    ResCursor_SetTableAndInit(player, cursorTable);
    ResPlayer_Refresh(player);
}

// ResPlayer_AdvanceAndRefresh (provisional name): when func_020c323c on the player succeeds, ResPlayer_Refresh.
extern "C" void ResPlayer_AdvanceAndRefresh(u8 *player);
ARM void ResPlayer_AdvanceAndRefresh(u8 *player) {
    if (func_020c323c(player) != 0) {
        ResPlayer_Refresh(player);
    }
}

// ResPlayer_SeekAndRefresh (provisional name): when ResCursor_SeekAndReset to index succeeds, ResPlayer_Refresh.
extern "C" void ResPlayer_SeekAndRefresh(u8 *player, u32 index);
ARM void ResPlayer_SeekAndRefresh(u8 *player, u32 index) {
    if (ResCursor_SeekAndReset(player, index) != 0) {
        ResPlayer_Refresh(player);
    }
}
