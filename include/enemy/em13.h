#ifndef WIP_A_EM13_H
#define WIP_A_EM13_H

#include "engine/player.h"

// Grid origin used to turn world positions into map cells (data_0212c648, u16 pair at +0x18 / +0x1a).
typedef struct GridOrigin {
    u8 unk_00[0x18];
    u16 originX;
    u16 originY;
} GridOrigin;
extern GridOrigin data_0212c648;

// Actor-specific fields of em13 (Wizzrobe family). Offsets are those of Entity.
typedef struct Vars_em13 {
    /* 00 */ u8 unk_00[0x6c];
    /* 6c */ u16 entryFlag;      // 1 on the first frame after spawning
    /* 6e */ u8 unk_6e[2];
    /* 70 */ u16 warpX;          // warp home x (integer half), written by WizVanishInit and getpos
    /* 72 */ u16 warpY;          // warp home y
    /* 74 */ u16 waitFrames;     // frames to wait while invisible
    /* 76 */ u16 waitTimer;      // countdown for em13_wait
    /* 78 */ u16 cellX;          // map cell base x of the current position
    /* 7a */ u16 cellY;          // map cell base y
    /* 7c */ u16 subX;           // offset inside the cell; zero in both means "pick a player as the next target"
    /* 7e */ u16 subY;
} Vars_em13;
#define V(e) VARS(Vars_em13, e)

extern const EntityFunc em13_stateTable[];
extern const EntityFunc em13_actionTable[];
extern const u8 em13_hitbox[];
extern const s8 wizWarpOffsets[];
extern const s16 em13_randomCellOffsets[];
extern u16 data_0213492c[];   // spawn offset x per area (shared, declared in enemy/em12.h)
extern u16 em12_spawnOffsetY[];  // spawn offset y per area (em12_spawnOffsetY)

void WizVanishInit(Entity *e);
void WizWarpVanish(Entity *e);
void WizWarpAppear(Entity *e);
void nextMove(Entity *e);
BOOL em13_getpos(Entity *e);

#endif
