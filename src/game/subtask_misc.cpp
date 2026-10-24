#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"

// Subtask OAM helper, 0x0209ad08 (subtask_dispReset at 0x0209aa2c is parked in scratch/agentA/nonmatching).

extern "C" void func_020c37c8(void *oamManager);
extern "C" void func_020c39c4(void *oamManager);
extern u8 data_0217a23c[];
extern u8 data_0217d23c[];

// subtask_dma_oam() (0x0209ad08): updates the OAM manager and clears the counter at +0x460 of the object in data_0217d23c + 0x10c.
ARM void subtask_dma_oam(void) {
    func_020c37c8(data_0217a23c);
    func_020c39c4(data_0217a23c);
    *(u32 *)(*(u8 **)(data_0217d23c + 0x10c) + 0x460) = 0;
}
