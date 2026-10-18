#ifndef UNKNOWN_BOSS_02036CA4_HPP
#define UNKNOWN_BOSS_02036CA4_HPP

#include "Unknown/Player.hpp"

struct Vars_02036ca4 {
    /* 00 */ u8 unk_00[0x6e];
    /* 6e */ u16 unk_6e;
    /* 70 */ u8 unk_70;
    /* 71 */ u8 unk_71;
    /* 72 */ u8 unk_72;
    /* 73 */ u8 unk_73;
    /* 74 */ u8 unk_74[8];
    /* 7c */ u8 unk_7c;
    /* 7d */ s8 unk_7d;
};
#define V(e) VARS(Vars_02036ca4, e)

struct UnkStruct_0212c5ac {
    /* 00 */ u8 unk_00[7];
    /* 07 */ u8 unk_7;
    /* 08 */ u8 unk_8[4];
    /* 0c */ s32 unk_c;
};
extern UnkStruct_0212c5ac data_0212c5ac;
extern Entity *data_0212c648;
extern u8 data_0217d384;
extern const EntityFunc data_020d177c[];
extern const u8 data_020d1438[];
extern const u8 data_020d1428[];
extern const u8 data_020d70c8[];
extern s32 data_02134914;
extern u8 data_0212c504;
extern u8 data_0212c618;
extern const u16 data_020d142c[];
extern const u32 data_020cf9b8[];
extern const s16 data_020d7e58[];
extern const u8 data_020d1440[];
extern u16 data_0212c5bc;

extern "C" {
void func_020547ec(void);
void func_0208ae30(Entity *e);
void func_02076fe0(int sfx);
void *func_0208da4c(void);
int func_0208de54(void *a);
void func_02076988(Entity *e, int a, int b);
void func_020463f0(int a);
void func_02060a70(Entity *e);
void func_02049f0c(int a);
void func_02049eb8(void);
void func_02021ec4(const void *a, int b);
void func_0204625c(int a, int b);
Entity *func_0204bdb8(int id);
void func_0205031c(Entity *e, Entity *other);
u8 func_02086080(s16 x, s16 y, s16 tx, s16 ty);
u8 *func_02093b5c(void);
void func_0205396c(void);
void func_02026720(void);
void func_0204fd40(Entity *e);
void func_02037f6c(Entity *e);
BOOL func_0203808c(Entity *e);
void func_02038138(Entity *e);
int func_020384b8(Entity *e);
void func_02038194(Entity *e);
BOOL func_020381ec(Entity *e);
void func_020382fc(Entity *e);
void func_02038414(Entity *e);
void func_020383bc(Entity *e);
void func_02076a50(Entity *e, int a, int b, int c);
void func_02038460(Entity *e);
void func_02053958(void);
void func_020899e4(Entity *e);
void func_020384f8(void);
void func_020266f8(void);
}

#endif
