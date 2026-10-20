#ifndef WIP_A_SS_H
#define WIP_A_SS_H

#include "engine/functions.h"
#include "global.h"
#include "object/set46.h"

extern const EntityFunc ssCursorTable[]; // ssCursorTable, indexed by action
extern const u16 ssCurAnimBoundsA[];     // ssCurAnimBoundsA, pairs indexed by KnifeApp index (ssCurAnimBoundsA)
extern const u16 ssCurAnimBoundsB[];     // ssCurAnimBoundsB, pairs indexed by KnifeApp index (ssCurAnimBoundsB)

// Byte at offset 0xcb0 of the KnifeApp instance (the cursor index)
#define KNIFE_CURSOR_INDEX() (((u8 *)KnifeApp_getInstance())[0xcb0])

void ss_panel(Entity *e);
void ss_cursor(Entity *e);
void ss_cur_init(Entity *e);
void ss_cur_move(Entity *e);

#endif
