#ifndef WIP_A_SUBTASK_INIT_H
#define WIP_A_SUBTASK_INIT_H

#include "engine/functions.h"
#include "game/subtask.h"

// Subtask init and title helpers from 0x0209bad8 to 0x0209c88c that other units do not declare yet.
extern "C" void subTask_init_bg3(int a, int b, int c);
extern "C" void subTask_init_bg2(int a, int b, int c);
extern "C" void subTask_init_bg2_lang(int a, int b);
extern "C" void subTask_init_obj_lang(int a, int b);
extern "C" void func_020a3778(u32 a);
void func_020827a8(s32 a); // C++ name _Z13func_020827a8l

#endif
