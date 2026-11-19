#ifndef GAME_CLEARKEY_LEVEL_H
#define GAME_CLEARKEY_LEVEL_H

#include "engine/functions.h"

extern "C" {
int ClearKeyLevelCheck(void); // 0x02048de8 (ClearKeyLevelCheck): 1 while a player lacks flag 8 or a level-1 key set,
                              // 2 while a level-2 key set is missing, otherwise 3 (all level-3 keys) or 2
}

#endif
