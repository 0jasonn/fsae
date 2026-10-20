#ifndef WIP_A_EFFECT_MORI_H
#define WIP_A_EFFECT_MORI_H

#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"

// One spawn record of birdSet (8 bytes, indexed by Random() & 3)
typedef struct BirdRecord {
    /* 00 */ u16 x;
    /* 02 */ u16 y;
    /* 04 */ u16 direction;
    /* 06 */ u16 speed;
} BirdRecord;

extern const EntityFunc effectMoriTable[]; // effectMoriTable, indexed by action
extern const BirdRecord birdRecords[];     // birdRecords, data_02116104

void effect_mori(Entity *e);
void effect_mori_init(Entity *e);
void effect_mori_wait(Entity *e);
void birdSet(Entity *e);
void effect_mori_move(Entity *e);

#endif
