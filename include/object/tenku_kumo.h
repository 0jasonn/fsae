#ifndef WIP_A_TENKU_KUMO_H
#define WIP_A_TENKU_KUMO_H

#include "engine/functions.h"
#include "global.h"
#include "object/set46.h"

extern const EntityFunc tenkuKumoTable[]; // tenkuKumoTable, indexed by action
extern u8 data_021349c0[];                // shared state block (ResultState in enemy/ending.h); read as s16 at +0x26
int ZeldaFadeFlagGet(void);

void tenku_kumo(Entity *e);
void tenku_kumo_init(Entity *e);
void tenku_kumo_move(Entity *e);

#endif
