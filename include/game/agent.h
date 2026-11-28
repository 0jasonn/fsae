#ifndef GAME_AGENT_H
#define GAME_AGENT_H

#include "engine/functions.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/dc_cache.h"
#include "sdk/os/os_irq.h"

// Prototypes for functions defined in src/wip/A/ (Implementer A).
// Plain (unmangled) functions get C linkage here; the original debug names of mangled ones are C++.

extern "C" {
// Defined in this directory, not yet in engine/functions.h.
void em0b_init(Entity *e);
int areacheck2(Entity *e);
void em16_getdir(Entity *e);
void kamen_init(Entity *e);
void em21_buttobi(Entity *e);
void WM_DataSharingReceiveSlot(void *base, u32 index, void *src);

// Engine / Knife helpers called by these units (missing from engine/functions.h).
void func_02084828(Entity *e);
void *WmGetSharedDataAddress(void *base, u32 mask, void *shared, u32 index);
u32 MATH_CountPopulation(u32 value);
void WM_SetPortCallback(u32 port, u32 a, u32 b);
}

// C++ functions defined in this directory (mangled original names).
void cockpit_obj_set(u8 index);
void getdir(Entity *e);
u8 charMove(Entity *e, u8 mode);

// Data used by these units.
extern u8 data_0212c420[];
extern const u8 em2b_hitbox[];   // em2b_hitbox
extern const u8 em1c_charAnimTable[];   // em1c_charAnimTable
extern const u8 em16_timerTable[];   // em16_timerTable
extern const s8 getdir_offsetTable[];   // getdir_offsetTable
extern const u8 data_020d3224[];   // em27 hitbox
extern u32 data_02134a68[];        // background animation slots (8 x 8 bytes)


#endif
