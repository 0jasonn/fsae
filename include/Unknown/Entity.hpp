#ifndef UNKNOWN_ENTITY_HPP
#define UNKNOWN_ENTITY_HPP

#include "types.h"

// Game object shared by the actor update functions. Field meanings are not known yet.
struct Entity {
    u8 unk_00[0xc];
    s32 unk_0c;
    s32 unk_10;
    u8 unk_14;
    u8 unk_15[2];
    u8 unk_17; // timer
    u8 unk_18[0x12];
    u8 unk_2a; // animation/direction
    u8 unk_2b;
    u8 unk_2c[6];
    s16 unk_32;
    u8 unk_34[0xb];
    u8 unk_3f;
    u8 unk_40[0x18];
    s32 unk_58;
};

extern "C" {
int func_020847c8(Entity *e);
void func_02085980(Entity *e);
void func_020859e0(Entity *e, u8 anim);
void func_02085f80(int sfx);
void func_02086200(Entity *e, int a);
int func_0204fdf0(Entity *e, s32 a);
}

#endif
