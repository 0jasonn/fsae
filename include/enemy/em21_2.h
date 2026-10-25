#ifndef WIP_B_EM21_2_H
#define WIP_B_EM21_2_H

#include "engine/functions.h"
#include "enemy/em21.h"

extern u16 frameCounter; // frame counter (frameCounter)
extern const u8 em21_hitbox[]; // em21_hitbox, hitbox of em21
extern u8 data_0212ced6[];      // per slot flags, stride 0x94 (checked by em21_crossCheck)
extern u8 data_0212ced8[];      // per slot Entity pointer, stride 0x94

extern "C" void func_02084828(Entity *e); // thumb helper, no original name yet
void MizupochaSet(Entity *e);              // original MizupochaSet(OBJ_WORK_*)
u8 em21_crossCheck(Entity *e);            // original crossCheck(OBJ_WORK_*)

// Actor-specific fields of em21 (Entity offsets 0x70 onwards).
typedef struct Vars_em21 {
    u8 unk_00[0x70];
    u16 posX;         // 0x70: x of the actor when it was killed, copied to the revived one
    u16 posY;         // 0x72: y of the actor when it was killed
    u16 revivalTimer; // 0x74: frames until revival (0x23a set by em21_die), 0 while alive
    u16 waitTimer;    // 0x76: frames to wait before the next jump
} Vars_em21;

extern const EntityFunc em22_stateTable[]; // em22_stateTable, state table of em22
extern "C" void Em22(Entity *e); // entry of em22, dsd Em22

#endif
