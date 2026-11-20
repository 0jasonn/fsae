#ifndef GAME_COM_H
#define GAME_COM_H

#include "engine/entity.h"

#include "engine/com_work.h"

void ComFinish(u32 a);                    // original ComFinish(unsigned long)
extern "C" {
void func_020281a8(void);
void func_020281ac(void);
}

#endif
