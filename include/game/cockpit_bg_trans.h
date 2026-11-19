#ifndef GAME_COCKPIT_BG_TRANS_H
#define GAME_COCKPIT_BG_TRANS_H

#include "engine/functions.h"

// Cockpit background page transfer (original cockpit_bg_trans()), 0x020272d8.
void cockpit_bg_trans(void);
void bg_trans_body(void); // original bg_trans_body(), 0x020272a8

#include "engine/cockpit_state.h"

#endif
