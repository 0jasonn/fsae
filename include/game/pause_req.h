#ifndef GAME_PAUSE_REQ_H
#define GAME_PAUSE_REQ_H

#include "types.h"

// Pause state block (pauseState, 0x20 bytes: Scene_ResetOverlayState and pause_4 clear all of it; set40Slots follows).
typedef struct PauseState {
    /* 00 */ u8 count;        // pause phase: indexes pauseHandlerTable; incremented by pause_req and pause_start
    /* 01 */ u8 option;       // chosen pause option (1..3, pause_exit)
    /* 02 */ u8 mode;         // delay timer: 3 from pause_req, 0x1e from pause_start; counted down by pause_req_wait
    /* 03 */ u8 kind;         // requesting player (pause_req's argument, read by pause_req_wait)
    /* 04 */ u8 unk_04;
    /* 05 */ u8 pauseBlocked; // Scene_SetFlag5/Scene_ClearFlag5; nonzero makes pause_init return at once
    /* 06 */ u16 textId;      // message of the pause window (pause_start: 0x7d6 wireless, 0x9ca otherwise)
    /* 08 */ u16 unk_08;
    /* 0a */ u8 unk_0a;       // cleared by pause_start, passed to the pause window setup
    /* 0b */ u8 unk_0b;
    /* 0c */ u8 unk_0c;       // pause_start: 8 wireless, 7 otherwise; passed to the pause window setup
    /* 0d */ u8 unk_0d;
    /* 0e */ u8 resetFlag;    // cleared by pause_start and pause_exit
    /* 0f */ u8 unk_0f;       // set when the wireless session is being closed
    /* 10 */ u8 unk_10[0x20 - 0x10];
} PauseState;

extern PauseState pauseState;

#endif
