#include "engine/functions.h"
#include "engine/menusound.h"

// SndState_StartEntry2 (0x020c186c): starts the sound of a menu sound entry for a reference. A voice is taken from the
// pool, the sequence (kind 6 lookup) and the sound data (lookup 1) are acquired for it; when one of them fails the
// voice is released and 0 is returned. On success the sequence is prepared and the entry bytes and the fade
// (index) are applied to the reference.
s32 SndState_StartEntry2(void * volatile *ref, s32 pool, s32 id, s32 priority, MenuSoundEntry *entry, s32 index) {
    void *voice;
    void *record;
    MenuSoundData *data;
    MenuSoundData *seq;
    s32 zero;

    voice = SndVoicePool_Start(ref, pool, priority);
    if (voice == NULL) {
        return 0;
    }
    record = SndVoicePool_Acquire(pool, voice);
    zero = 0;
    if (func_020c0e50(id, 6, record, zero, &seq) != 0) {
        ((void (*)(s32))Menu_ForwardBfd1c)((s32)voice);
        return zero;
    }
    if (func_020c0d6c(index, 1, record, zero, &data) != 0) {
        ((void (*)(s32))Menu_ForwardBfd1c)((s32)voice);
        return zero;
    }
    func_020bfd28(voice, (u8 *)data + data->dataOffset, zero, (s32)seq);
    Menu_SetRefByte40(ref, entry->byte6);
    SndRef_setPriority(ref, entry->byte7);
    MenuSound_SetFade(ref, index);
    return 1;
}

// SndState_StartEntryOwned (0x020c1970): like SndState_StartEntry2, but the sound data comes from the caller (data)
// and the entry word is the second value passed to the sequence; the fade times are set from fadeIn and fadeOut
s32 SndState_StartEntryOwned(void * volatile *ref, s32 pool, s32 id, s32 priority, MenuSoundEntry *entry, MenuSoundData *data, s32 fadeIn, s32 fadeOut) {
    void *voice;
    void *record;
    MenuSoundData *seq;
    s32 zero;

    voice = SndVoicePool_Start(ref, pool, priority);
    if (voice == NULL) {
        return 0;
    }
    record = SndVoicePool_Acquire(pool, voice);
    zero = 0;
    if (func_020c0e50(id, 6, record, zero, &seq) != 0) {
        ((void (*)(s32))Menu_ForwardBfd1c)((s32)voice);
        return zero;
    }
    func_020bfd28(voice, (u8 *)data + data->dataOffset, *(s32 *)entry, (s32)seq);
    Menu_SetRefByte40(ref, entry->byte6);
    SndRef_setPriority(ref, entry->byte7);
    MenuSound_SetFadeTimes(ref, fadeIn, fadeOut);
    return 1;
}
