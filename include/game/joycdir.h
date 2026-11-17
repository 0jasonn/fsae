#ifndef GAME_JOYCDIR_H
#define GAME_JOYCDIR_H

#include "engine/entity.h"

extern "C" {
u8 JoyCdirSet(Entity *e); // 0x02050200, original name, unmangled
}

#endif
