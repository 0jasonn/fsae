#ifndef WIP_E_MENUSOUND_E_H
#define WIP_E_MENUSOUND_E_H

#include "engine/functions.h"

// Entry of the menu sound table: the byte at +6 goes to the reference (Menu_SetRefByte40), +7 to SndRef_setPriority
typedef struct MenuSoundEntry {
    u8 unk_00[6];
    u8 byte6;
    u8 byte7;
} MenuSoundEntry;

// Result record of the sound data lookups: +0x18 is the offset of the sequence data from the record
typedef struct MenuSoundData {
    u8 unk_00[0x18];
    s32 dataOffset;
} MenuSoundData;

extern "C" {
void *SndVoicePool_Start(void * volatile *ref, s32 pool, s32 priority);
void *SndVoicePool_Acquire(s32 pool, void *voice);
s32 func_020c0d6c(s32 index, u32 flags, void *record, s32 flag, MenuSoundData **out);
s32 func_020c0e50(s32 index, u32 flags, void *record, s32 flag, MenuSoundData **out);
void func_020bfd28(void *voice, void *data, s32 a, s32 b);
void SndRef_setPriority(void * volatile *ref, u8 value);
void Menu_SetRefByte40(void * volatile *ref, u8 value);
void MenuSound_SetFadeTimes(void * volatile *ref, s32 fadeIn, s32 fadeOut);
void MenuSound_SetFade(void * volatile *ref, s32 value); // the ROM callers pass a full word (menu_api.h has u16)
}
void Menu_ForwardBfd1c(s32 a, s32 b, s32 c, s32 d);

extern "C" {
s32 SndState_StartEntry2(void * volatile *ref, s32 pool, s32 id, s32 priority, MenuSoundEntry *entry, s32 index);
s32 SndState_StartEntryOwned(void * volatile *ref, s32 pool, s32 id, s32 priority, MenuSoundEntry *entry, MenuSoundData *data, s32 fadeIn, s32 fadeOut);
}

#endif
