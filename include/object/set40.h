#ifndef WIP_A_SET40_H
#define WIP_A_SET40_H

#include "engine/functions.h"

// Actor fields of the Set40 family (file-local overlay).
typedef struct Vars_Set40 {
    /* 00 */ u8 unk_00[0x74];
    /* 74 */ u8 slot;          // index into set40Slots, set from e->type2
    /* 75 */ u8 unk_75;
    /* 76 */ u16 timerValue;   // set40TimerTable[e->timer] at init
    /* 78 */ u16 savedX;       // x.HALF.HI after the offset is applied
    /* 7a */ u16 savedY;       // y.HALF.HI after the offset is applied
    /* 7c */ u16 value;        // stored into set40Slots[slot] by Set40 in mode 0
    /* 7e */ u16 mode;         // 0 = main, 1 = lift, 2 = nemoto setup
} Vars_Set40;

extern const EntityFunc set40Table[];     // set40Table, mode 0, indexed by action
extern const EntityFunc set40AltTable[];  // set40AltTable, mode 1, indexed by action
extern const EntityFunc set40LiftTable[]; // set40LiftTable, indexed by subAction - 5
extern const s8 set40OffsetTable[];       // set40OffsetTable, dx/dy pairs per type
extern const u8 set40TimerTable[];        // set40TimerTable, indexed by timer
extern const u8 set40HitboxOdd[];         // set40HitboxOdd
extern const u8 set40HitboxEven[];        // set40HitboxEven
extern u16 set40Slots[];                  // set40Slots

void nemoto_init(Entity *e);
void nemoto_setdist(Entity *e);

#endif
