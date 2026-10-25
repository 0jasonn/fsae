#ifndef WIP_B_EM18_UNITS_H
#define WIP_B_EM18_UNITS_H

#include "engine/functions.h"

// Dispatch table of em18 indexed by the state from func_02084a30 (was data_020d2968, also the table GenericKnockback
// gets in enemy/em18.cpp). Proposed name: em18_stateTable.
extern const EntityFunc data_020d2968[];

// Type 0 handler of em18 (enemy/em18_3.cpp).
void em18_type0(Entity *e);

// Sets up the rock-on state of type 0 (enemy/type0rock.cpp). Not in functions.h yet.
void type0rockonSet(Entity *e);

// Hitbox table shared by em18 (defined by enemy/em05.h users as em06_hitbox).
extern const u8 em06_hitbox[];

// Height offset per animation frame (em18_heightTable, used by em18_move).
extern const s8 em18_heightTable[];
// Direction offsets of getdir (getdir_offsetTable).
extern const s8 getdir_offsetTable[];

// Turn of the actor: getdir alternates a 0x70 flag (wide or narrow turn).
typedef struct Vars_em18 {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u8 turnFlag;
} Vars_em18;

#define VARS_EM18(e) VARS(Vars_em18, e)

// Picks a new direction from the facing towards the parent, with a random offset.
void getdir(Entity *e);

#endif
