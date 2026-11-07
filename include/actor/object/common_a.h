#ifndef WIP_A_COMMON_A_H
#define WIP_A_COMMON_A_H

// Declarations shared by the files of implementer A (gameplay/comm code).
// GameState_UpdatePhase returns BOOL, but functions.h declares it void: hide that declaration and declare it here.
#define GameState_UpdatePhase GameState_UpdatePhase_voidDecl
#include "engine/functions.h"
#undef GameState_UpdatePhase
#include "engine/player.h"

extern "C" BOOL GameState_UpdatePhase(void);

// Frame counter block (frameCounter at 0x0212c5bc)
typedef struct FrameCounterBlock {
    /* 00 */ u16 frame;
    /* 02 */ u16 timer; // generic countdown used by the scene state machines
    /* 04 */ u8 unk_04[0xd];
    /* 11 */ u8 pauseFlag;
    /* 12 */ u8 unk_12;
    /* 13 */ u8 inputLock;
} FrameCounterBlock;
extern FrameCounterBlock frameCounter;

// Fade request (blendRequest at 0x0212c5ac): blendEnabled stays nonzero while a fade is running
typedef struct FadeRequest {
    /* 00 */ u8 blendEnabled;
} FadeRequest;
extern FadeRequest blendRequest;

extern u8 messageRequest[]; // scene control bytes: low 7 bits of [0] are the mode
extern u8 localPlayerIndex;
extern u8 data_0212c500; // game phase
extern u8 data_0212c4dc; // sub-state of the current phase
extern VoidFunc data_0212c564; // per-frame hook


void time_bonus(void);              // 0x020482e4
void ScrollMove(void);              // 0x02056f0c
void BgAnm(void);                   // 0x02023b50
void PlayerTrans(void);             // 0x02054d30
void DispCtrlClear(void);           // 0x0202a700
void func_0208309c(void);           // thumb
extern "C" {
void ClearNewStageUpdate(void);
void Cockpit(void);
}

#endif
