#ifndef UNKNOWN_D_MISC_D_H
#define UNKNOWN_D_MISC_D_H

#include "Unknown/Entity.h"
#include "Unknown/Player.h"

typedef void (*VoidFunc)(void);

// Node of the intrusive entity lists whose heads are data_0212c6b0[]; the links sit at the start of Entity
typedef struct EntityNode {
    struct EntityNode *prev;
    struct EntityNode *next;
} EntityNode;

typedef struct UnkStruct_0216fcf8 {
    /* 00 */ u8 unk_0;
    /* 01 */ u8 unk_1;
    /* 02 */ u16 unk_2;
    /* 04 */ s32 unk_4;
    /* 08 */ s32 unk_8;
} UnkStruct_0216fcf8;
extern UnkStruct_0216fcf8 data_0216fcf8;

typedef struct UnkStruct_0212c5ac_D {
    /* 00 */ u8 unk_0;
    /* 01 */ u8 unk_1;
    /* 02 */ u8 unk_2[5];
    /* 07 */ u8 unk_7;
    /* 08 */ s16 unk_8;
    /* 0a */ u8 unk_a[2];
    /* 0c */ s32 unk_c;
} UnkStruct_0212c5ac_D;
extern UnkStruct_0212c5ac_D data_0212c5ac;

typedef struct UnkStruct_0212c75c {
    /* 00 */ u16 unk_0;
    /* 02 */ u8 unk_2[0x14];
    /* 16 */ u16 unk_16;
    /* 18 */ u8 unk_18[0xc];
    /* 24 */ u16 unk_24;
    /* 26 */ u8 unk_26[0x40];
    /* 66 */ u16 unk_66;
    /* 68 */ u16 unk_68;
} UnkStruct_0212c75c;
extern UnkStruct_0212c75c data_0212c75c;

typedef struct UnkStruct_0212c648_D {
    /* 00 */ u8 unk_0[0x22];
    /* 22 */ s16 unk_22;
} UnkStruct_0212c648_D;
extern UnkStruct_0212c648_D data_0212c648;

extern EntityNode data_0212c6b0[];
extern EntityNode data_0212c6f0[];
extern u16 data_0216fd04[];
extern u16 data_02170104[];
extern u8 data_0212c500;
extern u8 data_0212c4dc;
extern u8 data_0212c5bc[];
extern u16 data_0212c594;
extern u8 data_021349c0[];
extern VoidFunc data_0212c564;
extern const VoidFunc data_02104a40[];
extern const u16 data_02104a58[];
extern const u32 data_02104a20;
extern const VoidFunc data_02104a24[];

void func_02050880(s32 a, s32 b);
void func_02050910(void);
void func_02050924(Entity *e);
void func_02050fe0(void);
void func_02049c7c(s32 a, s32 b, s32 c);
void func_020152c8(void);
void func_020152ec(void);
void func_02049c54(void);
void func_02082c54(void *fn);
void func_02014c24(s32 a);
void GX_TrySetBankForLCDC(s32 bank);
void MIi_CpuCopyFast(const void *src, void *dst, s32 size);
void *func_0208da4c(void);
void *func_0208dde0(void *a, s32 *size, s32 id);
u8 *func_0208ddcc(void *a, s32 id);
void func_02050ef0(void);
void DeleteEntity(Entity *e);
void func_0208455c(void);
void func_02076fe0(u32 a);
void func_02029d0c(s32 a, s32 b);
void func_0204625c(s32 a, s32 b);
void func_020463f0(s32 a);
void func_02029c60(s32 a, s32 b, s32 c);
void func_020830ec(void);
void func_02080ed4(void);

#endif
