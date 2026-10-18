#ifndef UNKNOWN_ENTITY_HPP
#define UNKNOWN_ENTITY_HPP

#include "types.h"

// 16.16 fixed point value whose integer half is also accessed on its own
union FixedPoint {
    s32 WORD;
    struct {
        u16 LO;
        s16 HI;
    } HALF;
};

struct Entity;
typedef void (*EntityFunc)(Entity *e);

// Game object shared by the actor update functions. Field meanings are not known yet.
struct Entity {
    /* 00 */ u8 unk_00[8];
    /* 08 */ u8 unk_08;
    /* 09 */ u8 unk_09;
    /* 0a */ u8 unk_0a;
    /* 0b */ u8 unk_0b;
    /* 0c */ s32 unk_0c; // speed
    /* 10 */ s32 unk_10;
    /* 14 */ u8 unk_14; // action
    /* 15 */ u8 unk_15; // subaction
    /* 16 */ u8 unk_16;
    /* 17 */ u8 unk_17; // timer
    /* 18 */ u8 unk_18;
    /* 19 */ u8 unk_19;
    /* 1a */ u8 unk_1a;
    /* 1b */ u8 unk_1b;
    /* 1c */ struct {
        u32 b0 : 2;
        u32 b2 : 2;
        u32 b4 : 2;
        u32 b6 : 2;
        u32 b8 : 6;
        u32 b14 : 2;
        u32 b16 : 4;
        u32 b20 : 4;
        u32 b24 : 6;
        u32 b30 : 2;
    } unk_1c;
    /* 20 */ u8 unk_20;
    /* 21 */ u8 unk_21;
    /* 22 */ u8 unk_22;
    /* 23 */ u8 unk_23;
    /* 24 */ u8 unk_24[4];
    /* 28 */ u8 unk_28;
    /* 29 */ u8 unk_29;
    /* 2a */ u8 unk_2a; // animation state
    /* 2b */ u8 unk_2b; // direction
    /* 2c */ u16 unk_2c;
    /* 2e */ u8 unk_2e;
    /* 2f */ u8 unk_2f;
    /* 30 */ FixedPoint unk_30; // x
    /* 34 */ FixedPoint unk_34; // y
    /* 38 */ FixedPoint unk_38; // z
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
    /* 4c */ Entity *unk_4c;
    /* 50 */ u16 unk_50;
    /* 52 */ u8 unk_52;
    /* 53 */ u8 unk_53;
    /* 54 */ Entity *unk_54;
    /* 58 */ Entity *unk_58;
    /* 5c */ u8 unk_5c[2];
    /* 5e */ struct {
        u8 b0 : 2;
        u8 b2 : 2;
        u8 b4 : 4;
    } unk_5e;
    /* 5f */ u8 unk_5f;
    /* 60 */ Entity *unk_60;
    /* 64 */ u8 unk_64[6];
    /* 6a */ u8 unk_6a;
    /* 6b */ u8 unk_6b;
    /* 6c */ u8 unk_6c[0x20]; // depends on the kind of actor, see each actor's Vars struct
};

// Accesses the actor-specific fields of an entity through the file's own struct
#define VARS(type, e) ((type *)(e))

extern "C" {
u32 func_0208455c(void); // random
int func_020847a0(Entity *e);
int func_020847c8(Entity *e);
void func_02084700(Entity *e);
void func_020849f4(Entity *e, const void *funcs);
void func_02084a7c(Entity *e, const void *funcs);
u32 func_02084ac8(Entity *e, int a);
Entity *func_02084f18(void);
void func_020852ec(Entity *e);
int func_020856cc(Entity *e, int a);
void func_02085980(Entity *e);
void func_020859e0(Entity *e, u8 anim);
void func_02085f80(int sfx);
int func_02086044(Entity *e, int a);
void func_02086200(Entity *e, int a);
Entity *func_02045eb4(void);
int func_0204fdf0(Entity *e, Entity *target);
Entity *func_02076858(int id, int a, int b);
}

#endif
