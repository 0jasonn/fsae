#ifndef GAME_RANKING_PLAYER_H
#define GAME_RANKING_PLAYER_H

#include "engine/functions.h"

extern Entity *mapState;     // 0x0212c648, first word: entity the camera follows
extern u8 localPlayerIndex;  // 0x0212c504

void ranking_player_set(void); // 0x02055194 (original name ranking_player_set())

#endif
