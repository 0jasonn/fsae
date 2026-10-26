#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_f.h"

// ctrl_find: functions Ctrl_findEntryA (0x020bbe50) to Ctrl_findEntryE (0x020bbf20), provisional names. Each looks the id
// up with Fs_GetDirFileOffset and returns the entry when its check (a different function per entry) accepts it, otherwise 0.

// Ctrl_findEntryA(self, id) (0x020bbe50, provisional name): the entry of id when ResChunk_OpenKBEC accepts it
extern "C" void *Ctrl_findEntryA(void *self, s32 id);
ARM void *Ctrl_findEntryA(void *self, s32 id) {
    void *entry;

    entry = Fs_GetDirFileOffset(id);
    if (entry != NULL) {
        if (ResChunk_OpenKBEC(entry, self) != 0) {
            return entry;
        }
    }
    return NULL;
}

// Ctrl_findEntryB(self, id) (0x020bbe84, provisional name): the same with Menu_ForwardC2cb4
extern "C" void *Ctrl_findEntryB(void *self, s32 id);
ARM void *Ctrl_findEntryB(void *self, s32 id) {
    void *entry;

    entry = Fs_GetDirFileOffset(id);
    if (entry != NULL) {
        if (Menu_ForwardC2cb4(entry, self) != 0) {
            return entry;
        }
    }
    return NULL;
}

// Ctrl_findEntryC(self, id) (0x020bbeb8, provisional name): the same with ResChunk_OpenRACH
extern "C" void *Ctrl_findEntryC(void *self, s32 id);
ARM void *Ctrl_findEntryC(void *self, s32 id) {
    void *entry;

    entry = Fs_GetDirFileOffset(id);
    if (entry != NULL) {
        if (ResChunk_OpenRACH(entry, self) != 0) {
            return entry;
        }
    }
    return NULL;
}

// Ctrl_findEntryD(self, id) (0x020bbeec, provisional name): the same with ResChunk_OpenTTLP
extern "C" void *Ctrl_findEntryD(void *self, s32 id);
ARM void *Ctrl_findEntryD(void *self, s32 id) {
    void *entry;

    entry = Fs_GetDirFileOffset(id);
    if (entry != NULL) {
        if (ResChunk_OpenTTLP(entry, self) != 0) {
            return entry;
        }
    }
    return NULL;
}

// Ctrl_findEntryE(self, id) (0x020bbf20, provisional name): the same with ResChunk_GetNRCS
extern "C" void *Ctrl_findEntryE(void *self, s32 id);
ARM void *Ctrl_findEntryE(void *self, s32 id) {
    void *entry;

    entry = Fs_GetDirFileOffset(id);
    if (entry != NULL) {
        if (ResChunk_GetNRCS(entry, self) != 0) {
            return entry;
        }
    }
    return NULL;
}
