#ifndef WIP_D_LOCAL_DECLS_H
#define WIP_D_LOCAL_DECLS_H

// Implementer D: prototypes of functions the D files call that functions.h does not declare yet.
// The reviewer moves these into include/engine/functions.h (or the matching module header).
// Functions whose symbol is unmangled in config/eur/arm9/symbols.txt are declared extern "C".
#include "engine/entity.h"
#include "game/rankingsave.h"

typedef struct FSFile {
    u8 unk_00[0x48]; // FS file handle, layout not known yet
} FSFile;

void set0b_itemAdd(Entity *e); // 0x02057f30, set_3.cpp
void set0a_setenemy(Entity *e); // 0x02057dec, set_6.cpp
void SetInit(Entity *e); // 0x02057614, not yet written
u16 CalcChecksum(const u16 *data, s32 size); // 0x02056120, backup.cpp
s32 Knife_fatRead(u16 slot, _SAVEHEADER *header); // 0x020565e8, backup_2.cpp
s32 Knife_mediaVerify(u16 slot, const u32 *data, s32 size); // 0x0205657c, parked in scratch/agentD/nonmatching

extern "C" {
u32 OS_GetBootType(void);
void *func_020c8104(void); // returns the Knife::PowerManager object
void FS_InitFile(FSFile *file);
s32 func_02010b1c(FSFile *file, const char *path, s32 mode); // open
u32 FS_GetFileLength(FSFile *file);
void FS_ReadFile(FSFile *file, void *buffer, u32 size);
void FS_CloseFile(FSFile *file);
void FS_CreateFile(const char *path, u32 mode);
void FS_SetFileLength(FSFile *file, u32 length);
void FS_WriteFileAsync(FSFile *file, const void *buffer, u32 size);
void FS_WaitAsync(FSFile *file);
void BlockCopy(const void *src, void *dst, u16 x, u16 y);
void func_0208ae14(void); // thumb
}

#endif
