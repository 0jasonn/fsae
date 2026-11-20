#ifndef GAME_ZMEM_H
#define GAME_ZMEM_H

#include "engine/functions.h"

void *zMalloc(u16 size); // original zMalloc(unsigned short), 0x0202a39c
void zFree(void *p); // original zFree(void*)

#endif
