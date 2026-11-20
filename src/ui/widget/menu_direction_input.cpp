#include "engine/functions.h"
#include "ui/widget/menu_direction_input.h"
#include "ui/widget/menu.h"
#include "ui/widget/ctrl_flags.h"

extern "C" {
void RectObjPair_setHitFlags(void *obj, u8 first, u8 second);
}

// Handle pressed or held vertical-scroll input; state names follow the provisional menu model.
extern "C" s32 func_020bd830(MenuWork *menu) {
    u8 up;
    u8 down;
    s32 handled;
    s32 state;
    u16 keys;

    if (Ctrl_isReady(menu->unk_358) != 0) {
        return 0;
    }

    state = menu->sub.state;
    up = 0;
    down = up;
    handled = up;
    if (state == 0) {
        keys = *(u16 *)&menu->sub.unk_3a0[0];
        if (keys & 0x40) {
            up = 1;
        } else if (keys & 0x80) {
            down = 1;
        }
        if (up != 0 || down != 0) {
            if (func_020be518(&menu->sub.unk_370, up, down) != 0) {
                menu->sub.state = 4;
                handled = 1;
                RectObjPair_setHitFlags(menu->unk_360, up, down);
                menu->sub.unk_398 = 1;
            } else {
                Menu_AcquirePoolEntry((u8 *)menu + 0xfc, 5, 0x80);
            }
        }
    } else if (state == 4) {
        keys = *(u16 *)&menu->sub.unk_3a0[4];
        if (keys & 0x40) {
            up = 1;
        } else if (keys & 0x80) {
            down = 1;
        }
        if (up != 0 || down != 0) {
            handled = 1;
            func_020be518(&menu->sub.unk_370, up, down);
        } else {
            menu->sub.state = 0;
            RectObjPair_setHitFlags(menu->unk_360, 0, 0);
        }
    }
    return handled;
}
