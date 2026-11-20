#ifndef GAME_RUPEELEVEL_H
#define GAME_RUPEELEVEL_H

#include "engine/entity.h"

int getRupeeLevel(void);       // 0x02082054
void rupee_error(u16 message); // 0x02082094, original rupee_error(unsigned short)

#endif
