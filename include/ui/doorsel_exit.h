#ifndef UI_DOORSEL_EXIT_H
#define UI_DOORSEL_EXIT_H

#include "engine/functions.h"
#include "engine/player.h"
#include "ui/doorsel_4.h"
#include "game/yousei.h"

extern u8 doorsel_difficultyBySelection[]; // doorsel_difficultyBySelection: game state byte 3 for each door selection
#include "engine/palette_buff.h"

// 0x0202b470, original doorsel_exit()
void doorsel_exit(void);

#endif
