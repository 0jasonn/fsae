#include "engine/functions.h"
#include "game/decls_g.h"
#include "ui/ctrl_scroll.h"
#include "ui/widget/menu.h"

extern "C" void Menu_Redraw(MenuWork *menu) {
    u8 changed;
    s32 i;
    s32 value340;
    s32 value344;
    s16 outA[2];
    s16 outB[2];

    func_020bed14((u8 *)menu + 0xfc);
    changed = 0;
    if (func_020be66c(&menu->sub.unk_370, &changed) != 0) {
        RectObjPair_updateFlags(menu->unk_360, menu->sub.scroll38c);
        for (i = 0; i < 2; i++) {
            RectObjPair_setValue(menu->views[i], menu->sub.scroll38c);
        }
    }
    if (changed != 0) {
        Menu_AcquirePoolEntry((u8 *)menu + 0xfc, 11, 128);
    }
    func_020be798((u8 *)menu + 0x40370);
    DC_FlushRange((u8 *)menu + 0x370, 0x40000);
    value340 = *(s32 *)((u8 *)menu + 0x340);
    value344 = *(s32 *)((u8 *)menu + 0x344);
    RectObjPair_countDownBoth(menu->unk_360);
    RectObjPair_updateChildren(menu->views[0], *(s32 *)((u8 *)menu + 0x344));
    RectObjPair_updateChildren(menu->views[1], *(s32 *)((u8 *)menu + 0x340));
    Ctrl_updateScroll((CtrlScrollObj *)menu->unk_358);
    outA[0] = 0;
    outA[1] = 0;
    ((MenuVirtualObj *)*(void **)((u8 *)menu + 0x34c))->slot1(&value344, outA);
    outB[0] = 0;
    outB[1] = 0;
    ((MenuVirtualObj *)*(void **)((u8 *)menu + 0x350))->slot1(&value340, outB);
}
