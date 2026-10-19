#ifndef UNKNOWN_ENTITY_H
#define UNKNOWN_ENTITY_H

#include "types.h"

// 16.16 fixed point value whose integer half is also accessed on its own
typedef union FixedPoint {
    s32 WORD;
    struct {
        u16 LO;
        s16 HI;
    } HALF;
} FixedPoint;

typedef struct Entity Entity;
typedef void (*EntityFunc)(Entity *e);

// Game object shared by the actor update functions. Field meanings are not known yet.
typedef struct Entity {
    /* 00 */ u8 unk_00[8];
    /* 08 */ u8 unk_08;
    /* 09 */ u8 unk_09;
    /* 0a */ u8 type;
    /* 0b */ u8 type2;
    /* 0c */ s32 speed; // speed
    /* 10 */ s32 zVelocity;
    /* 14 */ u8 action; // action
    /* 15 */ u8 subAction; // subaction
    /* 16 */ u8 unk_16;
    /* 17 */ u8 timer; // timer
    /* 18 */ u8 subtimer;
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
    } spriteSettings;
    /* 20 */ u8 unk_20;
    /* 21 */ u8 unk_21;
    /* 22 */ u8 unk_22;
    /* 23 */ u8 unk_23;
    /* 24 */ u8 unk_24[4];
    /* 28 */ u8 unk_28;
    /* 29 */ u8 frame;
    /* 2a */ u8 animationState; // animation state
    /* 2b */ u8 direction; // direction
    /* 2c */ u16 unk_2c;
    /* 2e */ u8 unk_2e;
    /* 2f */ u8 unk_2f;
    /* 30 */ FixedPoint x; // x
    /* 34 */ FixedPoint y; // y
    /* 38 */ FixedPoint z; // z
    /* 3c */ u8 unk_3c;
    /* 3d */ u8 iframes;
    /* 3e */ u8 unk_3e;
    /* 3f */ u8 unk_3f;
    /* 40 */ u8 unk_40;
    /* 41 */ u8 contactFlags;
    /* 42 */ u8 unk_42;
    /* 43 */ u8 unk_43;
    /* 44 */ u8 unk_44;
    /* 45 */ u8 health;
    /* 46 */ s8 unk_46;
    /* 47 */ u8 unk_47;
    /* 48 */ const void *hitbox;
    /* 4c */ Entity *contactedEntity;
    /* 50 */ u16 unk_50;
    /* 52 */ u8 unk_52;
    /* 53 */ u8 unk_53;
    /* 54 */ Entity *parent;
    /* 58 */ Entity *child;
    /* 5c */ u16 unk_5c;
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
} Entity;

// Accesses the actor-specific fields of an entity through the file's own struct
#define VARS(type, e) ((type *)(e))

#ifdef __cplusplus
extern "C" {
#endif
u32 Random(void); // random
int func_020847a0(Entity *e);
int func_020847c8(Entity *e);
void func_02084700(Entity *e);
void GenericKnockback(Entity *e, const void *funcs);
void EnemyFunctionHandler(Entity *e, const void *funcs);
u32 func_02084ac8(Entity *e, int a);
Entity *func_02084f18(void);
void func_020852ec(Entity *e);
int UpdateGravity(Entity *e, int a);
void UpdateAnimationSingleFrame(Entity *e);
void InitAnimationForceUpdate(Entity *e, u8 anim);
void EnqueueSFX(int sfx);
int func_02086044(Entity *e, int a);
void func_02086200(Entity *e, int a);
Entity *EmGetAimPl(void);
int GetFacingDirection(Entity *e, Entity *target);
Entity *GetSetWork(int id, int a, int b);
#ifdef __cplusplus
}
#endif

#endif
