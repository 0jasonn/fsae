#include "engine/functions.h"
#include "global.h"
#include "game/fileselui_e.h"

// Functions in this file (plain names from the debug build, C linkage):
//   fileSelUIView_checkSaveStatus (0x020a76d0)

void Task_Chain(u8 index);
extern "C" s32 fileSelUIView_checkSaveStatus(void *self);
extern "C" void func_020ac038(s32 a, s32 b, s32 c, s32 d);
extern u8 data_021350b0[];

// fileSelUIView::checkSaveStatus() (0x020a76d0): looks at the state of the three save entries; the states 3 and 4 start a
// task chain, 6 and 7 pick a result, and a result shows the status through func_020ac038
ARM s32 fileSelUIView_checkSaveStatus(void *self) {
    u8 i;
    s32 result;
    u8 *entry;

    result = 0;
    for (i = 0; i < 3; i++) {
        entry = data_021350b0 + i * 0x50;
        switch ((s8)entry[0x47]) {
        case 3:
        case 4:
            Task_Chain(11);
            break;
        case 7:
            result = 5;
            break;
        case 6:
            result = 4;
            break;
        }
    }
    if (result == 0) {
        return 0;
    }
    func_020ac038(result, (u8)(i + 1), 0, 0);
    return 1;
}
