#ifndef ENGINE_KEY_RING_H
#define ENGINE_KEY_RING_H

#include "types.h"

// Key sync ring of the multiplayer link: every player's keys of the last 16 frames.
extern u32 data_0212c538;        // frame counter of the ring (communication mode / sync state below 8); slot = counter & 0xf
extern u16 data_02134cb0[4 * 16]; // four 16-entry key tables (one per player, 0x20 bytes apart); 0xc000 = no keys yet

#endif
