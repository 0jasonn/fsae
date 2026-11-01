#ifndef WIP_B_TAMA11_H
#define WIP_B_TAMA11_H

// Tama11 / Throw module (src/wip/B/tama11.cpp, throwinit.cpp): the tama11 flying object, the Throw actor and the
// helpers they share. Callees and data that engine/functions.h does not declare yet.
#include "engine/functions.h"
#include "engine/player.h"

// Actor-specific fields of tama11 and Throw objects, from 0x64 on (offsets are Entity offsets).
typedef struct Tama11Vars {
    u8 unk_00[0x64];
    u16 copiedKind;    // 0x64: objKind of the child, copied by throw_init and compared in throw_move
    u16 copiedId;      // 0x66: objId of the child, copied the same way
    u8 unk_68[8];
    u16 expireTimer;   // 0x70: counts down in tama11_move1; at zero sets statusFlags 0x80
    u16 fiveMoveTimer; // 0x72: counts down in fiveMove; reset to 5 when it reaches zero
    u8 frameCounter;   // 0x74: advanced by tama11_move1 on each contact frame
    u8 phaseLength;    // 0x75: subtimer limit that switches tama11_move1 to its second phase
} Tama11Vars;

// Game state byte (data_0212c7c8 + off), see GAME_STATE_U8 in ending.h.
#define TAMA_GAME_STATE_BYTE(off) (*((u8 *)&data_0212c7c8 + (off)))
// Byte inside a player's PlayerData entry (data_0212ceb0[i] + off).
#define TAMA_PLAYER_BYTE(i, off) (((u8 *)&data_0212ceb0[i])[off])

void fiveMove(Entity *e);
void prtDamage(Entity *e);
void Throw(Entity *e);
void tama11_throw_init(Entity *e);
void throw_move(Entity *e);
void throwinit(Entity *e);
void tama11_putObjWorkThunk(Entity *e);

extern "C" void func_0208b658(Entity *e);
int func_02083ed8(Entity *e, Entity *target);
extern "C" void func_02089989_unk(PlayerData *pl);

extern u8 data_0212c4b8;

// Rodata tables used by the tama11 / Throw code.
extern const u8 tama11_spriteTable[][3];
extern const u8 tama11_throwHitbox[];
extern const u8 tama11_throwParams[][4];
extern const EntityFunc Throw_stateTable[];
extern const s32 tama11_speedTable[];
extern const s32 tama11_zVelTable[];
// Pointer table with 0x94-byte entries, indexed by sprite kind (see tama11_move1).
extern u8 tama11_objTemplates[];

#endif
