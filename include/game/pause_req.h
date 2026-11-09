#ifndef WIP_K_PAUSE_REQ_H
#define WIP_K_PAUSE_REQ_H

#include "types.h"

// Pause request block at pauseState (game/scene.h declares it as u8[]; a struct is proposed there).
typedef struct PauseState {
    /* 00 */ u8 count;   // incremented by every pause_req
    /* 01 */ u8 unk_01;
    /* 02 */ u8 mode;    // set to 3 by pause_req
    /* 03 */ u8 kind;    // the requested kind
} PauseState;

extern PauseState pauseState;

#endif
