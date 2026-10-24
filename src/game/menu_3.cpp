#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// Handles one input request: the event kind picks an action, then flag5 sets the state and flag6 clears it.
ARM s32 Menu_HandleInput(MenuWork *menu, MenuInput *input) {
    MenuEvent event;
    s32 handled;

    handled = func_020ba9a4(menu->unk_358, &event, input);
    if (handled != 0) {
        switch (event.kind) {
        case 1:
            Menu_Finish(menu);
            break;
        case 2:
            Menu_UpdateView(menu, event.value == 1);
            break;
        case 3:
            Menu_Step(menu, event.value == 1);
            break;
        case 4:
        case 5:
            func_020be154(menu);
            break;
        }
        if (input->flag5 != 0) {
            menu->sub.state = 2;
        }
    }
    if (input->flag6 != 0) {
        menu->sub.state = 0;
        handled = 1;
    }
    return handled;
}

// Second input handler: kind 0 with flag5 starts the timer block at 0xfc, kind 1 sets the active state, and flag6 clears it.
ARM s32 Menu_HandleInputB(MenuWork *menu, MenuInput *input) {
    MenuEventB event;
    s32 handled;

    if (menu->unk_360 == NULL) {
        return 0;
    }
    handled = 0;
    if (func_020b8554(menu->unk_360, &event, input) != 0) {
        handled = 1;
        switch (event.kind) {
        case 1:
            if (menu->sub.state != 1) {
                menu->sub.unk_398 = 1;
                menu->sub.state = 1;
            }
            func_020be518(menu->sub.unk_370, event.a, event.b);
            break;
        case 0:
            if (input->flag5 != 0) {
                func_020beda0(menu->unk_0fc, 5, 0x80);
            }
            break;
        }
        if (input->flag6 != 0) {
            menu->sub.state = 0;
        }
    }
    return handled;
}
