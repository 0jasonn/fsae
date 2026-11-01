#ifndef WIP_C_POT_THROW_H
#define WIP_C_POT_THROW_H

#include "engine/entity.h"

// Local player index (0x0212c504); same declaration as in misc_d.h
extern u8 localPlayerIndex;

extern "C" {
void pot_throw_throw(Entity *e); // 0x0205ef50, plain name in symbols.txt
void pot_ware(Entity *e);        // 0x0205ee7c, plain name in symbols.txt
}

#endif
