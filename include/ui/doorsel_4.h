#ifndef WIP_A_DOORSEL_4_H
#define WIP_A_DOORSEL_4_H

// Declarations used by src/wip/A/doorsel_4.cpp (door select screen).
#include "engine/functions.h"
#include "actor/enemy/decls_b2.h"

extern u8 localPlayerIndex;
void func_0202809c(void);          // C++ linkage (ComFinish(0))
void ab_check(void);               // 0x0202aee4
extern "C" {
void doorsel_select(void);         // 0x0202af70
}

#endif
