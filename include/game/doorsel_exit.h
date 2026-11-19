#ifndef GAME_DOORSEL_EXIT_H
#define GAME_DOORSEL_EXIT_H

#include "engine/functions.h"
#include "engine/player.h"
#include "game/doorsel_4.h"
#include "game/yousei.h"

extern u8 doorsel_difficultyBySelection[]; // doorsel_difficultyBySelection: game state byte 3 for each door selection
extern u16 data_021355a0;

// 0x0202b470, original doorsel_exit()
void doorsel_exit(void);

#endif
