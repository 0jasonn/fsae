#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional names, role not confirmed):
//   Menu_ClearRef (Menu_ClearRef), Menu_ReleaseRef (Menu_ReleaseRef), Menu_GetSlotWord (Menu_GetSlotWord),
//   Menu_SetRefByte41 (Menu_SetRefByte41), Menu_SetRefByte40 (Menu_SetRefByte40)

extern u8 data_0218430c[];

// Menu_ClearRef (0x020bf954): clears the first word of the reference (no check).
extern "C" void Menu_ClearRef(void * volatile *ref);
ARM void Menu_ClearRef(void * volatile *ref) {
    *ref = 0;
}

// Menu_ReleaseRef (0x020bf960): when the reference holds an object, its first word is cleared and the reference too.
extern "C" void Menu_ReleaseRef(void * volatile *ref);
ARM void Menu_ReleaseRef(void * volatile *ref) {
    if (*ref != 0) {
        **(s32 **)ref = 0;
        *ref = 0;
    }
}

// Menu_GetSlotWord (0x020bf97c): halfword at the start of the table entry (0x24 bytes each) at data_0218430c.
extern "C" u16 Menu_GetSlotWord(s32 index);
ARM u16 Menu_GetSlotWord(s32 index) {
    return *(u16 *)((u8 *)data_0218430c + index * 0x24);
}

// Menu_SetRefByte41 (0x020bf994): sets the byte at +0x41 of the object in the reference, when there is one.
extern "C" void Menu_SetRefByte41(void * volatile *ref, u8 value);
ARM void Menu_SetRefByte41(void * volatile *ref, u8 value) {
    if (*ref != 0) {
        *(u8 *)((u8 *)*ref + 0x41) = value;
    }
}

// Menu_SetRefByte40 (0x020bf9a8): sets the byte at +0x40 of the object in the reference, when there is one.
extern "C" void Menu_SetRefByte40(void * volatile *ref, u8 value);
ARM void Menu_SetRefByte40(void * volatile *ref, u8 value) {
    if (*ref != 0) {
        *(u8 *)((u8 *)*ref + 0x40) = value;
    }
}
