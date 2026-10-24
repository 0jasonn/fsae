#ifndef WIP_D_KNIFE_SOUND_H
#define WIP_D_KNIFE_SOUND_H

#include "types.h"

// Knife::Sound slot type (Knife::Sound::SequenceHandle, 0x1c bytes). Polymorphic: its vtable (data_0211ab98) is
// slot 0/1 dtor, slot 2 isValid, slots 3-6 forward to the sequence player at +0x18. Only the call sites are
// written here; the vtable itself lives in the ROM.
typedef struct KnifeSoundSequenceHandle KnifeSoundSequenceHandle;
struct KnifeSoundSequenceHandle {
    virtual void dtorSlot();
    virtual void deletingDtorSlot();
    virtual s32 isValid();
    virtual void fwdPlayerSlot3();
    virtual void fwdPlayerSlot4();
    virtual void fwdPlayerSlot5();
    virtual void fwdPlayerSlot6();
    /* 04 */ u32 id;
    /* 08 */ u8 unk_08[0x10];
    /* 18 */ void *player; // sequence player, NULL while the slot is idle
};

// Knife::Sound::HandleFactory: 16 slots, bit i of usedFlags marks slot i in use
typedef struct KnifeSoundHandleFactory {
    /* 000 */ KnifeSoundSequenceHandle handles[16];
    /* 1c0 */ u32 usedFlags;
} KnifeSoundHandleFactory;

typedef struct KnifeSoundHeap {
    /* 00 */ void *base;
} KnifeSoundHeap;

// Knife::Sound::System globals: the sequence handle factory, two wave handles (0x20 bytes each), and a 16-entry table
// of 0xc-byte records
typedef struct KnifeSoundWaveHandle {
    /* 00 */ u8 unk_00[0x20];
} KnifeSoundWaveHandle;

// Knife::Sound::MemoryArchive: the vtable pointer is the first word, data_0211ab88 is its vtable
typedef struct KnifeSoundMemoryArchive {
    /* 00 */ void *vtbl;
    /* 04 */ u8 unk_04[0x10];
} KnifeSoundMemoryArchive;

extern "C" {
// Knife::Sound::HandleFactory (defined in knife_sound.cpp)
void Knife_Sound_HandleFactory_update(KnifeSoundHandleFactory *self);
KnifeSoundSequenceHandle *Knife_Sound_HandleFactory_create(KnifeSoundHandleFactory *self);
void Knife_Sound_HandleFactory_release(KnifeSoundHandleFactory *self, KnifeSoundSequenceHandle *handle);
KnifeSoundSequenceHandle *Knife_Sound_HandleFactory_find(KnifeSoundHandleFactory *self, u32 id);
void Knife_Sound_HandleFactory_pause(KnifeSoundHandleFactory *self, s32 pause);
// Calls into other units of the Knife sound code (dsd names until they are named)
void Knife_Sound_Handle_reset(void *handle);                                // Knife_Sound_Handle_reset
void Knife_Sound_Handle_update(void *handle);                               // Knife_Sound_Handle_update
void Knife_Sound_Handle_pause(void *handle, s32 pause);                     // Knife_Sound_Handle_pause
void Knife_Sound_Handle_Handle(void *handle);                               // Knife_Sound_Handle_Handle
void func_0208bee4(void *handle);                                                // base dtor of Handle
void *func_020c09d8(void *base, u32 size);
void func_0208bcd4(void *self);                                              // base ctor, sets the base vtable
void func_0208bcfc(void *self);                                              // base dtor, empty
KnifeSoundSequenceHandle *Knife_Sound_SequenceHandle_dtor_SequenceHandle_08c45c(KnifeSoundSequenceHandle *self); // Knife_Sound_SequenceHandle_dtor_SequenceHandle_08c45c
void func_0200c868(void *array, s32 count, u32 size, void *dtor);            // array destructor helper
void func_020c050c(void *p);
void func_020bf9fc(void *player);
void func_020bf9dc(void *player);
void Menu_SetRefByte41(void *player);
void SndSlot_ReleaseFirst(void *player, s32 a);
void SndSlot_ResetFirst(void *player);
extern char data_0211ab88[]; // MemoryArchive vtable
extern char data_0211ab98[]; // SequenceHandle vtable
s32 Knife_Sound_WaveHandle_isValid(void *handle);                           // Knife_Sound_WaveHandle_isValid
void Knife_Sound_WaveHandle_finalize(void *handle);                          // Knife_Sound_WaveHandle_finalize
void Knife_Sound_WaveHandle_dtor_WaveHandle_0904e0(void *handle);           // Knife_Sound_WaveHandle_dtor_WaveHandle_0904e0
void Knife_Sound_WaveHandle_setFlagByte(void *handle, s32 flag);            // Knife_Sound_WaveHandle_setFlagByte
void SndSys_Init(void);
void SndSys_Shutdown(void);
s32 func_020bf2b4(void);
void func_020bf25c(void);
void func_020bf388(s32 index, void *entry);
}

extern "C" {
extern KnifeSoundHandleFactory data_02171f74; // sound system's sequence handle factory
extern KnifeSoundWaveHandle data_02171e74[2];
extern u8 data_02171eb4[];
}

#endif
