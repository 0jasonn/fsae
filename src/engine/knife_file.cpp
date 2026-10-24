#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/knife_file.h"

// Knife::File::Entity constructor, destructors, the field accessors and sync, 0x0208c6b4 to 0x0208c7ac.
// Provisional names in scratch/agentD/renames.txt: Knife_File_Entity_ctor, Knife_File_Entity_fwd_08c75c, Knife_File_Entity_getField54, Knife_File_Entity_getField58, Knife_File_Entity_isReadDone.

extern "C" KnifeFileEntity *Knife_File_Entity_ctor(KnifeFileEntity *self, s32 arg);
ARM KnifeFileEntity *Knife_File_Entity_ctor(KnifeFileEntity *self, s32 arg) {
    self->prev = self;
    self->vtbl = data_0211abbc;
    self->next = self;
    self->readDone = 0;
    FS_InitFile(self->fsFile);
    Knife_File_Entity_fwd_08c75c(self, arg);
    return self;
}

extern "C" void Knife_File_Entity_dtor_Entity_08c6f4(KnifeFileEntity *self);
ARM void Knife_File_Entity_dtor_Entity_08c6f4(KnifeFileEntity *self) {
    self->vtbl = data_0211abcc;
    self->next->prev = self->prev;
    self->prev->next = self->next;
    self->prev = self;
    self->next = self;
}

extern "C" KnifeFileEntity *Knife_File_Entity_dtor_Entity_08c720(KnifeFileEntity *self);
ARM KnifeFileEntity *Knife_File_Entity_dtor_Entity_08c720(KnifeFileEntity *self) {
    self->vtbl = data_0211abcc;
    self->next->prev = self->prev;
    self->prev->next = self->next;
    self->prev = self;
    self->next = self;
    operator delete(self);
    return self;
}

extern "C" void Knife_File_Entity_fwd_08c75c(KnifeFileEntity *self, s32 arg);
ARM void Knife_File_Entity_fwd_08c75c(KnifeFileEntity *self, s32 arg) {
    func_02008280((u8 *)self + 0x5c, arg);
}

extern "C" u32 Knife_File_Entity_getField54(KnifeFileEntity *self);
ARM u32 Knife_File_Entity_getField54(KnifeFileEntity *self) {
    return self->unk_54;
}

extern "C" u32 Knife_File_Entity_getField58(KnifeFileEntity *self);
ARM u32 Knife_File_Entity_getField58(KnifeFileEntity *self) {
    return self->unk_58;
}

extern "C" u8 Knife_File_Entity_isReadDone(KnifeFileEntity *self);
ARM u8 Knife_File_Entity_isReadDone(KnifeFileEntity *self) {
    return self->readDone;
}

extern "C" void Knife_File_Entity_sync(KnifeFileEntity *self);
ARM void Knife_File_Entity_sync(KnifeFileEntity *self) {
    if (self->readDone == 0) {
        do {
            Knife_File_System_yieldThread();
        } while (self->readDone == 0);
    }
}
