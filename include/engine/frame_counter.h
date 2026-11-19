#ifndef ENGINE_FRAME_COUNTER_H
#define ENGINE_FRAME_COUNTER_H

#include "types.h"

// Frame counter block (frameCounter, 0x0212c5bc). Declared with its full 0x20-byte extent on purpose: the incomplete
// (unsized) declaration changed scheduling in some users. The game loop increments frame once per frame; enemies and
// objects use its low bits to pick a player or an animation phase.
typedef struct FrameCounterBlock {
    /* 00 */ u16 frame;
    /* 02 */ u16 timer;            // generic countdown used by the scene state machines (makemap, multiplay)
    /* 04 */ u8 unk_04[0x11 - 0x04];
    /* 11 */ u8 pauseRequest;     // running pause request: pause_req stores kind | 0x80, low 2 bits = requesting player;
                                  // nonzero blocks the HUD/menu input
    /* 12 */ u8 stopRequest;      // nonzero stops Encounter and makes multiplay_main end the stage (cleared by
                                  // multiplay_init)
    /* 13 */ u8 playersBound;     // set by BindPlayers; BeforeTask moves it into playersBoundPrev and clears it
    /* 14 */ u8 playersBoundPrev; // nonzero on the frame after BindPlayers (blocks the HUD/menu input)
    /* 15 */ u8 unk_15[0x20 - 0x15];
} FrameCounterBlock;
extern FrameCounterBlock frameCounter;

#endif
