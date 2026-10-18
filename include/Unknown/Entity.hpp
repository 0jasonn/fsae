#ifndef UNKNOWN_ENTITY_HPP
#define UNKNOWN_ENTITY_HPP

#include "types.h"

// Game object shared by the actor update functions. Field meanings are not known yet.
struct Entity {
    /* 00 */ u8 unk_00[0xc];
    /* 0c */ s32 unk_0c;
    /* 10 */ s32 unk_10;
    /* 14 */ u8 unk_14; // action
    /* 15 */ u8 unk_15[2];
    /* 17 */ u8 unk_17; // timer
    /* 18 */ u8 unk_18[4];
    /* 1c */ u32 unk_1c;
    /* 20 */ u8 unk_20[9];
    /* 29 */ u8 unk_29;
    /* 2a */ u8 unk_2a; // animation/direction
    /* 2b */ u8 unk_2b; // direction
    /* 2c */ u8 unk_2c[2];
    /* 2e */ u8 unk_2e;
    /* 2f */ u8 unk_2f[3];
    /* 32 */ s16 unk_32;
    /* 34 */ u8 unk_34[6];
    /* 3a */ s16 unk_3a;
    /* 3c */ u8 unk_3c;
    /* 3d */ u8 unk_3d;
    /* 3e */ u8 unk_3e;
    /* 3f */ u8 unk_3f;
    /* 40 */ u8 unk_40;
    /* 41 */ u8 unk_41;
    /* 42 */ u8 unk_42;
    /* 43 */ u8 unk_43[2];
    /* 45 */ u8 unk_45;
    /* 46 */ u8 unk_46[2];
    /* 48 */ const void *unk_48;
    /* 4c */ u8 unk_4c[0xc];
    /* 58 */ s32 unk_58;
    /* 5c */ u8 unk_5c[0x14];
    /* 70 */ u16 unk_70;
    /* 72 */ u16 unk_72;
    /* 74 */ u8 unk_74[8];
    /* 7c */ u8 unk_7c;
    /* 7d */ u8 unk_7d[3];
};

typedef void (*EntityFunc)(Entity *e);

extern "C" {
u32 func_0208455c(void); // random
int func_020847a0(Entity *e);
int func_020847c8(Entity *e);
void func_02084700(Entity *e);
void func_020849f4(Entity *e, const void *funcs);
void func_02084a7c(Entity *e, const void *funcs);
u32 func_02084ac8(Entity *e, int a);
s32 func_02084f18(void);
int func_020856cc(Entity *e, int a);
void func_020852ec(Entity *e);
void func_02085980(Entity *e);
void func_020859e0(Entity *e, u8 anim);
void func_02085f80(int sfx);
int func_02086044(Entity *e, int a);
void func_02086200(Entity *e, int a);
s32 func_02045eb4(void);
int func_0204fdf0(Entity *e, s32 a);
}

#endif
