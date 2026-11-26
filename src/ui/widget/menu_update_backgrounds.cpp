#include "engine/functions.h"
#include "ui/widget/menu_update_backgrounds.h"
#include "ui/widget/ctrl_wrap_api.h"
#include "ui/widget/menu.h"
#include "ui/widget/menu_scroll.h"
#include "sdk/fx/fx.h"

extern "C" {
void G2x_SetBGyAffine_(u32 reg, const void *matrix, s32 a, s32 b, s32 x, s32 y);
}

typedef void (*MenuSpanCallback)(void *dst, s32 offset, s32 size);
extern "C" void func_020bc43c(void *owner, const s16 *pos, MenuSpanCallback writeSpan);

void Menu_SetBlendLevel(MenuWork *menu, s32 level);

extern "C" void func_020bd128(MenuWork *menu, s32 offset) {
    s32 zero;
    s32 y;
    s32 secondY;
    s16 scroll;
    MtxFx22 matrix;
    s16 first[2];
    s16 second[2];

    Ctrl_updateSlotsA(*(void **)((u8 *)menu + 0x340));
    Ctrl_updateSlotsA(*(void **)((u8 *)menu + 0x344));
    Menu_applyBgScroll((MenuScrollObj *)menu->unk_358);
    MTX_Identity22_(&matrix);
    scroll = menu->sub.scroll38c;
    zero = 0;
    y = scroll - 0x12;
    G2x_SetBGyAffine_(0x04001030, &matrix, zero, zero, offset, y);
    secondY = y + 0xc0;
    G2x_SetBGyAffine_(0x04000030, &matrix, zero, zero, offset, secondY);
    if (offset == 0) {
        if (((*(volatile u32 *)0x04001000 & 0xe000) >> 13) != 0) {
            if (menu->unk_358->flagAd == 0) {
                *(volatile u32 *)0x04000000 &= ~0xe000;
            }
            *(volatile u32 *)0x04001000 &= ~0xe000;
        }
    } else {
        if (((*(volatile u32 *)0x04001000 & 0xe000) >> 13) == 0) {
            if (menu->unk_358->flagAd == 0) {
                *(volatile u32 *)0x04000000 = (*(volatile u32 *)0x04000000 & ~0xe000) | 0x2000;
            }
            *(volatile u32 *)0x04001000 = (*(volatile u32 *)0x04001000 & ~0xe000) | 0x2000;
        }
        Menu_SetBlendLevel(menu, offset);
    }
    first[0] = 0;
    first[1] = 0xae;
    func_020bc43c(&menu->sub.unk_370, first, Menu_Bg3WriteA);
    second[0] = 0xae;
    second[1] = 0x142;
    func_020bc43c(&menu->sub.unk_370, second, Menu_Bg3WriteB);
    *(s16 *)&menu->sub.unk_38e[2] = menu->sub.scroll38c;
    *(s16 *)&menu->sub.unk_38e[4] = *(s16 *)&menu->sub.unk_38e[0];
}
