#ifndef WIP_F_SET3E_H
#define WIP_F_SET3E_H

// Prototypes used by src/wip/F/set3e*.cpp that engine/functions.h does not declare yet (to be moved there).
#include "engine/functions.h"

int func_02083cdc(Entity *e); // 0x02083cdc, returns a small code compared with 0x22 and 0x43
extern "C" void EffectSet(Entity *e, int kind, int arg); // 0x02076a20, unmangled (set38.h)

#endif
