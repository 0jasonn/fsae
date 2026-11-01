#ifndef WIP_C_TAMA08_2_H
#define WIP_C_TAMA08_2_H

#include "engine/functions.h"

// Thumb callees of the tama08 wait/move helpers, plain symbols (extern "C")
extern "C" void func_0208af0c(Entity *e); // thumb, no original name
extern "C" int func_0208b668(Entity *e);  // thumb, returns nonzero when the actor is blocked

// State table of the Tama09 dispatcher, indexed by e->action (data_020dcf90)
extern const EntityFunc data_020dcf90[];

#endif
