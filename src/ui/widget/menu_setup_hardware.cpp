#include "engine/functions.h"
#include "ui/widget/slot_group_api.h"
#include "knife/app/twl.h"
#include "sdk/fx/stub_empty.h"
#include "ui/widget/menu.h"
#include "sdk/gx/gx.h"

extern "C" s32 func_0218a870(void);
extern "C" void func_020be9f0(void *obj);

// Copies the caller's 16-byte setup record, initializes the menu hardware state,
// and starts touch handling after preparing the menu's work subobject.
extern "C" void Menu_setupHardware(void *self, const void *param) {
    u8 *obj = (u8 *)self;
    u32 *dst = (u32 *)self;
    const u32 *src = (const u32 *)param;
    MenuWork *menu = (MenuWork *)self;
    s32 flag;
    s32 vblank;

    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    Os_InitCommonWrap();
    Stub_EmptyB();
    flag = (func_0218a870() != 0) ? 1 : 0;
    menu->sub.flag624 = (u8)flag;
    if ((flag & 0xff) == 0) {
        func_0218a860(1);
    }
    vblank = GX_VBlankIntr(1);
    menu->sub.flag623 = (vblank != 0) ? 1 : 0;
    func_02012c40();
    if (Ctrl_isSlotGroup() == 0) {
        GX_SetDefaultDMA(3);
        menu->sub.flag622 = 1;
    }
    GX_DispOff();
    *(volatile u32 *)0x04001000 &= ~0x10000;
    func_020be9f0(obj + 0x403a0);
    Menu_StartTouch(obj + 0x403a6);
    GX_VBlankIntr(1);
    Menu_ClearVram(menu);
}
