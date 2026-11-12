#ifndef ACTOR_OBJECT_SET53_ROW_H
#define ACTOR_OBJECT_SET53_ROW_H

#include "engine/functions.h"
#include "engine/player.h"

// set53 (the rowing boat): the boat seat object rides on its parent and carries two riders
typedef struct Vars_Set53 {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *rider0;    // rows with the timer flag (0x17)
    /* 68 */ Entity *rider1;    // rows with the subtimer flag (0x18)
    /* 6c */ u8 strokeTimer;    // frames left in the current stroke
    /* 6d */ u8 unk_6d;
    /* 6e */ u16 strokeAccel;   // added to the parent's speed each frame of the stroke
} Vars_Set53;

// The boat hull (parent of the seat)
typedef struct Vars_Set53Hull {
    /* 00 */ u8 unk_00[0x6c];
    /* 6c */ u32 speed;         // capped at 0x200
} Vars_Set53Hull;

extern u16 playerKeys[]; // keys of the communication slots
extern const s8 data_020db878[][2]; // rider x offsets, two per animation state
extern const s8 data_020db888[][2]; // rider y offsets, two per animation state
extern const u16 data_020db898[]; // rowing motion per facing
extern const s8 data_020db8cc[][9]; // seat animation per animation state, indexed by the two row flags

extern "C" {
void func_0208a954(Entity *e); // thumb
}

// C++ linkage (original names)
u8 set53_scrcheck(Entity *e, Entity *other, u8 flag);
void set53_move2(Entity *e);

#endif
