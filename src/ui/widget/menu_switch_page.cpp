#include "engine/functions.h"
#include "engine/gx_misc_api.h"
#include "game/decls_g.h"
#include "ui/widget/menu.h"
#include "ui/widget/menu_release.h"

// Provisional source interface: the ROM calls the resource lookup in vtable slot 3.
struct MenuPageSource {
    virtual void slot0(void);
    virtual void slot1(void);
    virtual void slot2(void);
    virtual void *find(u32 tag, const void *key);
};

extern "C" {
void func_020b4f00(void *message, void *holder, void *resource, void *source);
void *LobbyMsgObj_create(void *holder);
}

void Menu_ClearSlots(MenuWork *menu);
void Menu_SetBrightness(MenuWork *menu, s32 level);

extern "C" void func_020bdd60(MenuWork *menu, const void *key, void *source, s32 reverse) {
    s32 i;
    s32 level;
    s32 offset;
    s32 j;
    void *resource;
    MenuWork *holder;

    for (i = 0; i < 13; i++) {
        level = i * 16 / 12;
        Menu_Redraw(menu);
        OS_WaitVBlankIntr();
        Menu_SetBrightness(menu, level);
        offset = 0;
        if (level > 6) {
            offset = ((level - 6) << 6) / 10;
        }
        if (reverse != 0) {
            offset = -offset;
        }
        func_020bd128(menu, (s16)offset);
    }

    Menu_ClearSlots(menu);
    *(s16 *)((u8 *)menu->unk_360 + 0x1c) = 0;
    RectObjPair_updateFlags(menu->unk_360, 0);
    for (j = 0; j < 2; j++) {
        *(s16 *)((u8 *)menu->views[j] + 0x1a) = 0;
        RectObjPair_setValue(menu->views[j], 0);
    }
    Menu_Reset(menu);
    resource = ((MenuPageSource *)source)->find(0x6e747067, key);
    if (resource != NULL) {
        holder = menu;
        menu->sub.unk_39c = (s32)LobbyMsgObj_create(&holder);
        func_020b4f00((void *)menu->sub.unk_39c, &holder, resource, source);
        *(u16 *)((u8 *)menu->sub.unk_39c + 0x1c) = 0xae;
        Menu_SetActive((MenuList *)&menu->sub.unk_370, menu->sub.unk_39c);
        *(s16 *)((u8 *)menu->unk_360 + 0x1c) =
            (*(s16 **)&menu->sub.unk_370[4])[5];
        RectObjPair_updateFlags(menu->unk_360, menu->sub.scroll38c);
        for (j = 0; j < 2; j++) {
            *(s16 *)((u8 *)menu->views[j] + 0x1a) =
                (*(s16 **)&menu->sub.unk_370[4])[5];
            RectObjPair_setValue(menu->views[j], menu->sub.scroll38c);
        }
    }

    OS_WaitVBlankIntr();
    Gx_loadPalette(*(u16 *)((u8 *)menu->sub.unk_39c + 0xc));
    i = 13;
    while (i > 0) {
        i--;
        level = i * 16 / 12;
        Menu_Redraw(menu);
        OS_WaitVBlankIntr();
        Menu_SetBrightness(menu, level);
        offset = 0;
        if (level > 6) {
            offset = -((level - 6) << 6) / 10;
        }
        if (reverse != 0) {
            offset = -offset;
        }
        func_020bd128(menu, (s16)offset);
    }
    if (menu->unk_358->flagAd == 0) {
        Gx_setBlendAlpha();
    }
}
