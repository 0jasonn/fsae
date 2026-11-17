#ifndef GAME_COMERROR_WAIT_H
#define GAME_COMERROR_WAIT_H

#include "engine/functions.h"
#include "actor/enemy/ending.h"
#include "game/multiplay_main.h"

extern u8 data_0212c4dc; // phase of the communication error wait (0 reset, 1 count down)
extern u8 data_0212c4f8;
extern u8 data_0212c500;
extern u16 data_021355a0;

void subtask_dispReset(bool on); // original subtask_dispReset(bool), 0x0209aa2c

// 0x02028b58, original comerror_wait()
void comerror_wait(void);

#endif
