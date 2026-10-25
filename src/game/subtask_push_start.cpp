#include "engine/functions.h"
#include "global.h"
#include "game/subtask_a.h"

// subTask_push_start() (0x0209c88c): the "push start" screen. A blink counter toggles the screen mode every 45 frames,
// then after the first 30 frames the press sets the phase and the phase steps through the fade-out sequence.

extern u8 data_0212c4e4;
extern u16 data_0212c510;
extern u8 *data_0217d348;

// Display control word (REG_DISPCNT). Bits 8 to 12 are the layer enables toggled by the blink.
#define SUBTASK_DISPCNT (*(volatile u32 *)0x04001000)

// subTask_push_start() (0x0209c88c)
ARM void subTask_push_start(void) {
    SubtaskPushStartWork **work;

    if (data_0212c4e4 == 0 || data_0212c4e4 == 0xb) {
        SUBTASK_DISPCNT = SUBTASK_DISPCNT & ~0x1f00;
        return;
    }
    work = (SubtaskPushStartWork **)&data_0217d348;
    if ((*work)->phase == 0) {
        if ((*work)->frameCount % 45 == 0) {
            (*work)->blinkCount++;
            if ((*work)->blinkCount & 1) {
                SUBTASK_DISPCNT = (SUBTASK_DISPCNT & ~0x1f00) | 0x400;
            } else {
                SUBTASK_DISPCNT = SUBTASK_DISPCNT & ~0x1f00;
            }
        }
        if ((*work)->frameCount > 30) {
            if ((data_0212c510 & 9) != 0 || is_op_demo_end()) {
                (*work)->phase = 1;
                if (data_0212c510 & 9) {
                    SoundReq(0x3e);
                }
            }
        }
    } else {
        (*work)->phase++;
        if ((*work)->phase < 5) {
            SUBTASK_DISPCNT = (SUBTASK_DISPCNT & ~0x1f00) | 0x400;
        } else if ((*work)->phase < 10) {
            SUBTASK_DISPCNT = SUBTASK_DISPCNT & ~0x1f00;
        } else if ((*work)->phase < 15) {
            SUBTASK_DISPCNT = (SUBTASK_DISPCNT & ~0x1f00) | 0x400;
        } else if ((*work)->phase < 20) {
            SUBTASK_DISPCNT = SUBTASK_DISPCNT & ~0x1f00;
        } else if ((*work)->phase < 40) {
            SUBTASK_DISPCNT = (SUBTASK_DISPCNT & ~0x1f00) | 0x400;
        } else {
            SUBTASK_DISPCNT = SUBTASK_DISPCNT & ~0x1f00;
            func_020827a8(3);
            op_demo_skip();
        }
    }
    (*work)->frameCount++;
}
