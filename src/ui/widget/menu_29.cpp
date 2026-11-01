#include "engine/functions.h"
#include "global.h"
#include "ui/widget/menu.h"
#include "ui/widget/menu_wip.h"
#include "ui/widget/menu_api.h"

// Functions in this file (provisional names, role not confirmed):
//   Menu_AcquirePoolEntry (Menu_AcquirePoolEntry)

s32 Menu_InRange(void *self, s32 value, s32 low, s32 high);
s32 Menu_ClampValue(void *self, s32 value, s32 low, s32 high);
extern "C" MenuPoolEntry *Menu_FindPoolEntry(MenuPool *pool, s32 id);

// Menu_AcquirePoolEntry (0x020beda0): claims the entry for the id (the existing one, or a new one from Menu_AllocPoolEntry)
// when the pool is ready and the id is in range. The entry is cleared, and when value is not 0x80 its level is set
// from the clamped value. Returns the entry, or 0.
void *Menu_AcquirePoolEntry(void *poolObj, s32 id, s32 value) {
    MenuPool *pool = (MenuPool *)poolObj;
    MenuPoolEntry *entry;
    s32 level;

    if (pool->ready == 0) {
        return 0;
    }
    if (Menu_InRange(pool, id, 0, pool->count) == 0) {
        return 0;
    }
    entry = Menu_FindPoolEntry(pool, id);
    if (entry == 0) {
        entry = Menu_AllocPoolEntry(pool, 1);
    }
    if (entry == 0) {
        return 0;
    }
    SndSlot_ReleaseFirst(entry, 0);
    SndState_StartEntryList(entry, 0, id);
    if (value != 0x80) {
        level = Menu_ClampValue(pool, value, 0, 0xff);
        func_020bf9dc(entry, 0xffff, level - 0x80);
    }
    entry->id = id;
    entry->unk_08 = 0;
    return entry;
}

// Functions in this file (provisional names, role not confirmed):
//   Menu_FindPoolEntry (Menu_FindPoolEntry)

// Menu_FindPoolEntry (0x020bee6c): finds the entry in use with the id (the id must be in range 0..count, see
// Menu_InRange). Returns 0 when there is none.
MenuPoolEntry *Menu_FindPoolEntry(MenuPool *pool, s32 id) {
    u32 i;
    s32 offset;
    u8 *entry;

    if (Menu_InRange(pool, id, 0, pool->count) == 0) {
        return 0;
    }
    for (i = 0; i < 16; i++) {
        offset = i * 0x18;
        entry = (u8 *)pool + offset;
        if (id == *(s32 *)(entry + 0xb8)) {
            if (*(s32 *)(entry + 0xb4) != 0) {
                return (MenuPoolEntry *)((u8 *)pool + 0xb4 + offset);
            }
        }
    }
    return 0;
}

// Functions in this file (provisional names, role not confirmed):
//   Menu_AllocPoolEntry (Menu_AllocPoolEntry)

s32 Menu_WrapInto(void *self, s32 value, s32 a, s32 b);

// Menu_AllocPoolEntry (0x020beed4): moves the current index of the pool on by one (wrapped into 0..15) and looks for an
// entry that is not in use, starting there. The first free entry becomes current and is returned. When none is free and
// flag is set, the entry at the current index is returned (otherwise 0).
MenuPoolEntry *Menu_AllocPoolEntry(MenuPool *pool, s32 flag) {
    u32 i;
    s32 zero;
    s32 index;
    MenuPoolEntry *entry;

    i = 0;
    pool->current = Menu_WrapInto(pool, pool->current + 1, i, 0x10);
    zero = 0;
    for (i = 0; i < 16; i++) {
        index = Menu_WrapInto(pool, pool->current + i, zero, 0x10);
        if (pool->entries[index].unk_00 == 0) {
            pool->current = index;
            return &pool->entries[index];
        }
    }
    entry = 0;
    if (flag != 0) {
        entry = &pool->entries[pool->current];
    }
    return entry;
}

// Wraps the value into the range between a and b (the lower end is the smaller of the two): a value below the lower
// end gains the range, a value at or above the upper end loses it. The first argument is the caller object (unused).
s32 Menu_WrapInto(void *self, s32 value, s32 a, s32 b) {
    s32 range;
    s32 swap;

    range = b - a;
    if (range < 0) {
        swap = a;
        a = b;
        b = swap;
        range = swap - a;
    }
    if (value < a) {
        value += range;
    } else if (value >= b) {
        value -= range;
    }
    return value;
}

// Clamps the value into [low, high].
s32 Menu_ClampValue(void *self, s32 value, s32 low, s32 high) {
    if (value < low) {
        value = low;
    } else if (value > high) {
        value = high;
    }
    return value;
}

// Nonzero when low <= value < high.
s32 Menu_InRange(void *self, s32 value, s32 low, s32 high) {
    if (value >= low && value < high) {
        return 1;
    }
    return 0;
}

// Functions in this file (provisional names, role not confirmed):
//   Menu_CreateEntryDefault (Menu_CreateEntryDefault), Menu_CreateEntryEx (Menu_CreateEntryEx)

// Menu_CreateEntryDefault (0x020befd0): Menu_CreateEntryEx with a zero sixth argument.
extern "C" void Menu_CreateEntryDefault(void *out, void *checker, void *a, void *b, void *c);
void Menu_CreateEntryDefault(void *out, void *checker, void *a, void *b, void *c) {
    Menu_CreateEntryEx(out, checker, a, b, c, 0);
}

// Menu_CreateEntryEx (0x020beff4): looks up the object for id 0x40628 in the checker (func_020c2c34), makes it with
// func_020bc588 when the lookup found something, then creates the entry with RectBufSet_init and stores it in *out.
void Menu_CreateEntryEx(void *out, void *checker, void *a, void *b, void *c, u16 d) {
    s32 result;

    result = func_020c2c34((MenuChecker *)checker, 0x40628);
    if (result != 0) {
        result = func_020bc588(result);
    }
    RectBufSet_init(result, checker, a, b, c, d);
    *(s32 *)out = result;
}

// Runs the menu main sequence for the menu held by the wrapper.
void Menu_RunFromWrapper(MenuWrapper *w) {
    Menu_Run(w->ptr);
}

// Functions in this file (provisional names, role not confirmed):
//   Menu_ReleaseWrapper (Menu_ReleaseWrapper)

// Menu_ReleaseWrapper (0x020bf06c): releases the menu held by the wrapper (Menu_releaseBlocks), notifies Heap_VirtualFree and
// clears the wrapper pointer. Called by Knife_ForwardMenuWrapper.
extern "C" void Menu_ReleaseWrapper(MenuWrapper *wrapper, void *arg);
void Menu_ReleaseWrapper(MenuWrapper *wrapper, void *arg) {
    MenuWork *menu;

    menu = wrapper->ptr;
    Menu_releaseBlocks(menu);
    Heap_VirtualFree(arg, menu);
    wrapper->ptr = 0;
}
