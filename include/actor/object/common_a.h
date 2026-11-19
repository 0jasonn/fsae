#ifndef WIP_A_COMMON_A_H
#define WIP_A_COMMON_A_H

// Declarations shared by the files of implementer A (gameplay/comm code).
// GameState_UpdatePhase returns BOOL, but functions.h declares it void: hide that declaration and declare it here.
#define GameState_UpdatePhase GameState_UpdatePhase_voidDecl
#include "engine/functions.h"
#undef GameState_UpdatePhase
#include "engine/player.h"

extern "C" BOOL GameState_UpdatePhase(void);

#include "engine/frame_counter.h"

#include "engine/blend_request.h"

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
