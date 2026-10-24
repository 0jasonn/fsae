#ifndef WIP_D_KNIFE_FILE_H
#define WIP_D_KNIFE_FILE_H

#include "types.h"

// Knife::File::Entity: a node of a circular list (next/prev), with an FS file at +0x0c and a done flag at +0x9c
typedef struct KnifeFileEntity {
    /* 00 */ void *vtbl;
    /* 04 */ struct KnifeFileEntity *next;
    /* 08 */ struct KnifeFileEntity *prev;
    /* 0c */ u8 fsFile[0x48];
    /* 54 */ u32 unk_54;
    /* 58 */ u32 unk_58;
    /* 5c */ u8 unk_5c[0x40];
    /* 9c */ u8 readDone;
} KnifeFileEntity;

extern "C" {
void Knife_File_Entity_fwd_08c75c(KnifeFileEntity *self, s32 arg); // Knife_File_Entity_fwd_08c75c
void FS_InitFile(void *file);
void func_02008280(void *a, s32 b);
void Knife_File_System_yieldThread(void);
extern char data_0211abbc[]; // Knife::File::Entity vtable
extern char data_0211abcc[]; // vtable the dtors leave behind
}

#endif
