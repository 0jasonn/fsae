#include "engine/functions.h"
#include "global.h"

// Subtask: toggles the OBJ layer bit of the sub screen display control register. 0x0209aa2c subtask_dispReset

void subtask_dispReset(bool on) {
    volatile u32 *dispcnt = (volatile u32 *)0x04001000;

    if (on) {
        *dispcnt = (*dispcnt & ~0x1f00) | 0x1000;
    } else {
        *dispcnt = *dispcnt & ~0x1f00;
    }
}
