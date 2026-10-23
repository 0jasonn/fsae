#include "engine/functions.h"
#include "global.h"

// Task chaining, 0x02082ee0: Task_Chain remembers the previous task, sets the new one and clears the demo step.

extern u8 data_0212c4e4; // current task
extern u8 data_0212c4bc; // previous task
extern u8 data_0212c4dc; // demo sub-step
extern u8 data_0212c500; // demo step

// Task_Chain (0x02082ee0)
ARM void Task_Chain(u8 a) {
    if (data_0212c4e4 == 7 || data_0212c4e4 == 9) {
        OpeningTaskFinalzie();
    }
    data_0212c4bc = data_0212c4e4;
    data_0212c4e4 = a;
    data_0212c4dc = 0;
    data_0212c500 = 0;
}
