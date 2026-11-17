#ifndef GAME_COCKPIT_BG_TRANS_H
#define GAME_COCKPIT_BG_TRANS_H

#include "engine/functions.h"

// Cockpit background page transfer (original cockpit_bg_trans()), 0x020272d8.
void cockpit_bg_trans(void);
void bg_trans_body(void); // original bg_trans_body(), 0x020272a8

// Cockpit state block: [2] nonzero requests a full transfer, [3] page index, [0xb] bitmask of transferred pages.
extern u8 cockpitState[];

#endif
