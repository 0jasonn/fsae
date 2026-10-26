#include "engine/functions.h"
#include "global.h"

// Cursor_GetSpan (Cursor_GetSpan, provisional name): when the count at +8 is at most the last index at +6 plus one and the
// halfword at +4 is not above the last index, returns last - count + 1; otherwise 0.
extern "C" u16 Cursor_GetSpan(u8 *self);
ARM u16 Cursor_GetSpan(u8 *self) {
    u16 last;
    u16 count;
    u32 valid;

    last = *(u16 *)(self + 6);
    count = *(u16 *)(self + 8);
    valid = 0;
    if (count <= last + 1) {
        if (*(u16 *)(self + 4) <= last) {
            valid = 1;
        }
    }
    if (valid != 0) {
        return (u16)(last - count + 1);
    }
    return 0;
}

// Slots_ClearThree (Slots_ClearThree, provisional name): sets the three slots of the array to -1.
extern "C" void Slots_ClearThree(s32 *slots);
ARM void Slots_ClearThree(s32 *slots) {
    s32 i;

    for (i = 0; i < 3; i++) {
        slots[i] = -1;
    }
}

// Slots_Set (Slots_Set, provisional name): slots[index] = value.
extern "C" void Slots_Set(s32 *slots, u32 index, u32 value);
ARM void Slots_Set(s32 *slots, u32 index, u32 value) {
    slots[index] = value;
}

// Slots_ClearThreeAt8 (Slots_ClearThreeAt8, provisional name): sets the three words starting at +8 to -1.
extern "C" void Slots_ClearThreeAt8(u8 *self);
ARM void Slots_ClearThreeAt8(u8 *self) {
    s32 i;

    for (i = 0; i < 3; i++) {
        *(s32 *)(self + 8 + i * 4) = -1;
    }
}

// Slots_SetAt8 (Slots_SetAt8, provisional name): the word at +8 + index * 4 is set to value.
extern "C" void Slots_SetAt8(u8 *self, u32 index, u32 value);
ARM void Slots_SetAt8(u8 *self, u32 index, u32 value) {
    *(u32 *)(self + 8 + index * 4) = value;
}
