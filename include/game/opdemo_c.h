#ifndef WIP_C_OPDEMO_C_H
#define WIP_C_OPDEMO_C_H

// Opening-demo helpers used by the C units that the shared header does not declare yet.
#include "engine/functions.h"

void PutNPC(u8 index);                  // original PutNPC(unsigned char), frees an NPC slot from data_02134d30

extern u16 data_0212c510;               // flag word also declared in game/multiplay.h

// Engine and player helpers that are not in engine/functions.h yet (see report).
void RotateObjWork(u8 list);            // original RotateObjWork(unsigned char), 0x0204c1ec
extern "C" void func_020855bc(Entity *e); // dsd name (thumb label 0x020855bc), takes the player entity
extern u8 data_0212c4e8;                // byte cleared at the start of AfterPlayer
int func_02083d18(Entity *e, int dx, int dy); // C++ linkage (_Z13func_02083d18P9OBJ_WORK_ii), same as enemycommon.h
extern "C" void make_hyosyo(void);    // plain symbol, 0x020558c0 (ranking screen setup)
extern "C" void GameState_UpdatePhase(void); // plain symbol, 0x02049454, no arguments
extern "C" void ranking_hyosyo(void);   // plain symbol; parked in scratch/agentC/nonmatching (ranking_hyosyo)
extern u8 frameCounter[];              // ranking screen block, u16 timer at +2 (declared in another wip header as well)
extern u16 data_021355a0;

// Step index of the opening scene state machine (data_021349c0[0x0d], not named in misc_d.h yet)
enum {
    OPSCENE_SUBSTATE = 0x0d,
    OPSCENE_ACTIVE_SLOT = 0x0f, // slot of the running effect, 0xff when none (same byte as EFFECT_STATE_ACTIVE_SLOT)
};

#endif
