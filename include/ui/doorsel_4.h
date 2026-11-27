#ifndef UI_DOORSEL_4_H
#define UI_DOORSEL_4_H

// Declarations used by src/wip/A/doorsel_4.cpp (door select screen).
#include "engine/functions.h"
#include "knife/comm/comm.h"

void ab_check(void);               // 0x0202aee4
extern "C" {
void doorsel_select(void);         // 0x0202af70
}

#endif
