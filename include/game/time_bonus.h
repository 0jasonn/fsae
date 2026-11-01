#ifndef GAME_TIME_BONUS_H
#define GAME_TIME_BONUS_H

#include "engine/entity.h"

// PlayerData and GameState are defined in engine/player.h.
#include "engine/player.h"


// Timer-like block written by time_bonus
typedef struct TimerC {
    /* 00 */ u8 unk_00[8];
    /* 08 */ u32 unk_08;
    /* 0c */ u32 unk_0c;
    /* 10 */ u32 unk_10;
    /* 14 */ u32 unk_14;
} TimerC;
extern TimerC telopRequest;

#endif
