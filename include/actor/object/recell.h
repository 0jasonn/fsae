#ifndef ACTOR_OBJECT_RECELL_H
#define ACTOR_OBJECT_RECELL_H

#include "engine/functions.h"
#include "engine/player.h"

#include "engine/map_state.h"

extern const u16 *const recell0Cells[]; // recell0Cells, one list of replacement cell ids per block type
extern const u16 *const recell1Cells[]; // recell1Cells

void recell0(Entity *e);
void recell1(Entity *e);

#endif
