#ifndef UNKNOWN_B_ACTOR_0204112C_H
#define UNKNOWN_B_ACTOR_0204112C_H

#include "engine/player.h"

// Overlay for the enemy whose functions start at 0x0204112c (actor identity not known yet).
typedef struct Vars_0204112c {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *target;      // player the enemy tracks
    /* 68 */ u8 unk_68[0x8];
    /* 70 */ u16 subPosX;         // scroll position, stepped by 0x18 per frame
    /* 72 */ u16 subPosY;         // scroll position, stepped by 0x10 per frame
    /* 74 */ u8 restTimer;        // rest time saved when a pause ends
    /* 75 */ u8 turnActive;       // 1 while a turn towards the target is running
    /* 76 */ u8 turnStartDir;     // direction when the turn started
    /* 77 */ u8 retargetDelay;    // frames until the target is checked again
    /* 78 */ u16 turnTimeout;     // 0x12c frames
    /* 7a */ u16 idleTimer;       // countdown for em28_attackwait
} Vars_0204112c;
#define V(e) VARS(Vars_0204112c, e)

// Overlay for the parts of the enemy at 0x02042424: two child entities.
typedef struct Vars_Parts {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ Entity *partA;
    /* 7c */ Entity *partB;
} Vars_Parts;
#define VP(e) VARS(Vars_Parts, e)

// Overlay for the timer state of the enemy at 0x02042798.
typedef struct Vars_Timer {
    /* 00 */ u8 unk_00[0x74];
    /* 74 */ u8 stateCounter;
    /* 75 */ u8 unk_75;
    /* 76 */ u16 delay;           // 0x12c frames
} Vars_Timer;
#define VT(e) VARS(Vars_Timer, e)

// data_0212c648 is a shared symbol. Other headers declare it as Entity *; these are the fields this range reads.
typedef struct UnkStruct_0212c648 {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 unk_18;
    /* 1a */ u16 unk_1a;
} UnkStruct_0212c648;
extern UnkStruct_0212c648 data_0212c648;

typedef struct UnkStruct_021348cc {
    s32 unk_0;
    s32 unk_4;
} UnkStruct_021348cc;
extern UnkStruct_021348cc data_021348cc;
extern const u16 data_020d347a[];
extern u16 data_0212c574[3];



#endif
