#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/knife_sound.h"
#include "engine/knife_sound_api.h"

// Knife::Sound::HandleFactory, Knife::Sound::Heap, the static object, MemoryArchive, SequenceHandle and System::initialize,
// 0x0208c1c8 to 0x0208c530. Knife_Sound_System_update (0x0208c554) is nonmatching, see scratch/agentD/nonmatching.
// Provisional names in scratch/agentD/renames.txt: Knife_Sound_StaticObject_clear, Knife_Sound_StaticObject_dtor, Knife_Sound_MemoryArchive_ctor, Knife_Sound_SequenceHandle_ctor,
// Knife_Sound_SequenceHandle_fwdPlayer_08c4a0, Knife_Sound_SequenceHandle_fwdPlayer_08c4c4, Knife_Sound_SequenceHandle_getPlayerField, Knife_Sound_SequenceHandle_fwdPlayer_08c4dc, Knife_Sound_SequenceHandle_fwdPlayer_08c4ec, Knife_Sound_SequenceHandle_fwdPlayer_08c504, Knife_Sound_SequenceHandle_fwdPlayer_08c518.

extern "C" KnifeSoundHandleFactory *Knife_Sound_HandleFactory_dtor_HandleFactory(KnifeSoundHandleFactory *self);
KnifeSoundHandleFactory *Knife_Sound_HandleFactory_dtor_HandleFactory(KnifeSoundHandleFactory *self) {
    Frame_LoopC868(self, 16, sizeof(KnifeSoundSequenceHandle), (void *)Knife_Sound_SequenceHandle_dtor_SequenceHandle_08c45c);
    return self;
}

void Knife_Sound_HandleFactory_update(KnifeSoundHandleFactory *self) {
    int i;
    for (i = 0; i < 16; i++) {
        if (self->usedFlags & (1 << i)) {
            KnifeSoundSequenceHandle *handle = &self->handles[i];
            if (handle->isValid() == 0) {
                self->usedFlags &= ~(1 << i);
            } else {
                Knife_Sound_Handle_update(handle);
            }
        }
    }
}

KnifeSoundSequenceHandle *Knife_Sound_HandleFactory_create(KnifeSoundHandleFactory *self) {
    int i;
    for (i = 0; i < 16; i++) {
        if ((self->usedFlags & (1 << i)) == 0) {
            self->usedFlags |= (1 << i);
            Knife_Sound_Handle_reset(&self->handles[i]);
            return &self->handles[i];
        }
    }
    return NULL;
}

void Knife_Sound_HandleFactory_release(KnifeSoundHandleFactory *self, KnifeSoundSequenceHandle *handle) {
    int i;
    for (i = 0; i < 16; i++) {
        if (&self->handles[i] == handle) {
            self->usedFlags &= ~(1 << i);
            return;
        }
    }
}

KnifeSoundSequenceHandle *Knife_Sound_HandleFactory_find(KnifeSoundHandleFactory *self, u32 id) {
    int i;
    for (i = 0; i < 16; i++) {
        if (self->usedFlags & (1 << i)) {
            KnifeSoundSequenceHandle *handle = &self->handles[i];
            if (handle->isValid() != 0 && id == handle->id) {
                return handle;
            }
        }
    }
    return NULL;
}

void Knife_Sound_HandleFactory_pause(KnifeSoundHandleFactory *self, s32 pause) {
    int i;
    for (i = 0; i < 16; i++) {
        if (self->usedFlags & (1 << i)) {
            KnifeSoundSequenceHandle *handle = &self->handles[i];
            if (handle->isValid() != 0) {
                Knife_Sound_Handle_pause(handle, pause);
            }
        }
    }
}

// Static object used by the sound code: its constructor clears the first word, its destructor does nothing
void Knife_Sound_StaticObject_clear(u32 *self) {
    *self = 0;
}

void Knife_Sound_StaticObject_dtor(void *self) {
}

extern "C" bool Knife_Sound_Heap_initialize(KnifeSoundHeap *self, void *memory, u32 size);
bool Knife_Sound_Heap_initialize(KnifeSoundHeap *self, void *memory, u32 size) {
    self->base = SndHeap_CreateRecord(memory, size);
    return self->base != NULL;
}

extern "C" KnifeSoundMemoryArchive *Knife_Sound_MemoryArchive_ctor(KnifeSoundMemoryArchive *self);
KnifeSoundMemoryArchive *Knife_Sound_MemoryArchive_ctor(KnifeSoundMemoryArchive *self) {
    func_0208bcd4(self);
    self->vtbl = data_0211ab88;
    return self;
}

extern "C" KnifeSoundMemoryArchive *Knife_Sound_MemoryArchive_dtor_MemoryArchive_08c3f8(KnifeSoundMemoryArchive *self);
KnifeSoundMemoryArchive *Knife_Sound_MemoryArchive_dtor_MemoryArchive_08c3f8(KnifeSoundMemoryArchive *self) {
    knifeSoundNop1(self);
    return self;
}

extern "C" KnifeSoundMemoryArchive *Knife_Sound_MemoryArchive_dtor_MemoryArchive_08c40c(KnifeSoundMemoryArchive *self);
KnifeSoundMemoryArchive *Knife_Sound_MemoryArchive_dtor_MemoryArchive_08c40c(KnifeSoundMemoryArchive *self) {
    knifeSoundNop1(self);
    operator delete(self);
    return self;
}

extern "C" bool Knife_Sound_MemoryArchive_initialize(KnifeSoundMemoryArchive *self, void *data);
bool Knife_Sound_MemoryArchive_initialize(KnifeSoundMemoryArchive *self, void *data) {
    func_020c050c((u8 *)self + 4);
    return TRUE;
}

extern "C" KnifeSoundSequenceHandle *Knife_Sound_SequenceHandle_ctor(KnifeSoundSequenceHandle *self);
KnifeSoundSequenceHandle *Knife_Sound_SequenceHandle_ctor(KnifeSoundSequenceHandle *self) {
    Knife_Sound_Handle_Handle(self);
    *(void **)self = data_0211ab98;
    return self;
}

KnifeSoundSequenceHandle *Knife_Sound_SequenceHandle_dtor_SequenceHandle_08c45c(KnifeSoundSequenceHandle *self) {
    knifeSoundNop3(self);
    return self;
}

extern "C" KnifeSoundSequenceHandle *Knife_Sound_SequenceHandle_dtor_SequenceHandle_08c470(KnifeSoundSequenceHandle *self);
KnifeSoundSequenceHandle *Knife_Sound_SequenceHandle_dtor_SequenceHandle_08c470(KnifeSoundSequenceHandle *self) {
    knifeSoundNop3(self);
    operator delete(self);
    return self;
}

extern "C" s32 Knife_Sound_SequenceHandle_isValid(KnifeSoundSequenceHandle *self);
s32 Knife_Sound_SequenceHandle_isValid(KnifeSoundSequenceHandle *self) {
    return self->player != NULL;
}

extern "C" void Knife_Sound_SequenceHandle_fwdPlayer_08c4a0(KnifeSoundSequenceHandle *self);
void Knife_Sound_SequenceHandle_fwdPlayer_08c4a0(KnifeSoundSequenceHandle *self) {
    SndVoiceRef_SetTempo(&self->player);
}

extern "C" s32 Knife_Sound_SequenceHandle_getPlayerNumber(KnifeSoundSequenceHandle *self);
s32 Knife_Sound_SequenceHandle_getPlayerNumber(KnifeSoundSequenceHandle *self) {
    if (self->player == NULL) {
        return -1;
    }
    return *((u8 *)self->player + 0x3c);
}

extern "C" void Knife_Sound_SequenceHandle_fwdPlayer_08c4c4(KnifeSoundSequenceHandle *self, s32 a, s32 b);
void Knife_Sound_SequenceHandle_fwdPlayer_08c4c4(KnifeSoundSequenceHandle *self, s32 a, s32 b) {
    func_020bf9dc(&self->player);
}

extern "C" void *Knife_Sound_SequenceHandle_getPlayerField(KnifeSoundSequenceHandle *self);
void *Knife_Sound_SequenceHandle_getPlayerField(KnifeSoundSequenceHandle *self) {
    return &self->player;
}

extern "C" void Knife_Sound_SequenceHandle_fwdPlayer_08c4dc(KnifeSoundSequenceHandle *self);
void Knife_Sound_SequenceHandle_fwdPlayer_08c4dc(KnifeSoundSequenceHandle *self) {
    Menu_SetRefByte41(&self->player);
}

extern "C" void Knife_Sound_SequenceHandle_fwdPlayer_08c4ec(KnifeSoundSequenceHandle *self, s32 a);
void Knife_Sound_SequenceHandle_fwdPlayer_08c4ec(KnifeSoundSequenceHandle *self, s32 a) {
    Knife_Sound_SequenceHandle_fwdPlayer_08c4c4(self, 0xffff, a);
}

extern "C" void Knife_Sound_SequenceHandle_fwdPlayer_08c504(KnifeSoundSequenceHandle *self);
void Knife_Sound_SequenceHandle_fwdPlayer_08c504(KnifeSoundSequenceHandle *self) {
    SndSlot_ReleaseFirst(&self->player, 0);
}

extern "C" void Knife_Sound_SequenceHandle_fwdPlayer_08c518(KnifeSoundSequenceHandle *self);
void Knife_Sound_SequenceHandle_fwdPlayer_08c518(KnifeSoundSequenceHandle *self) {
    SndSlot_ResetFirst(&self->player);
}

extern "C" void Knife_Sound_System_initialize(void);
void Knife_Sound_System_initialize(void) {
    SndSys_Init();
    Knife_Sound_WaveHandle_setFlagByte(&data_02171e74[0], 0);
    Knife_Sound_WaveHandle_setFlagByte(&data_02171e74[1], 1);
}
