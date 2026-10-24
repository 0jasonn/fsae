#ifndef WIP_G_DECLS_G_H
#define WIP_G_DECLS_G_H

// Declarations used by the G units that are not in engine/functions.h yet. The reviewer moves the shared ones there.

#include "types.h"
#include "game/menu.h"

// Knife manual helper (0x020befd0, unnamed wrapper of the menu object creation; five arguments)
extern "C" void func_020befd0(void *a, void *b, void *c, void *d, void *e);

// Knife manual data (provisional names are the dsd names; data_0212c4dc is also used by the result sequence)
extern u8 data_021271ac[];
extern u8 data_02187070[];
extern s32 data_0212c524;
extern u8 data_0212c4dc;
extern u8 data_0212c57c[];
extern u16 data_021355a0;

// Calls made by Knife::i_restoreGfxSettings (dsd names, C linkage unless the symbol is mangled)
extern "C" {
void func_02012c40(void);
void func_02014af4(s32 a);
void func_020148f0(s32 a);
void func_02015084(u32 a);
void func_02015120(s32 a);
void GX_SetGraphicsMode(u32 a, u32 b, u32 c);
void OS_Terminate(void);
void Knife_Comm_WirelessIcon_initialize_16x16_ColorMode(void *icon, s32 colorType, s32 value);
}
void Irq_InitVBlank(void);

// Calls made by Knife::PowerManager::update and the PowerManager accessor (dsd or TwlSDK names)
extern "C" {
s32 PM_GetLCDPower(void);
s32 PM_SetLCDPower(s32 a);
void func_0201d038(s32 a, s32 b, s32 c);
void m4aSoundResume(void);
s32 func_02012e58(void);
void func_0200c574(void *obj, void (*destructor)(void *), void *dso);
void Knife_PowerManager_PowerManager(void *self);
void Knife_PowerManager_dtorComplete_PowerManager(void *self);
}
extern u8 data_0218709c[];
extern u8 data_02187090[];
extern u32 data_0218708c;

// Data used by disp_A_button (the OAM buffer is objAffineSet, see include/game/scene_d.h)
extern u8 objAffineSet[];
extern u8 data_0212c4c8;
extern u32 data_021870b0;
extern const u32 data_020df200[];

// Title and save-error screen data and calls (savefile_error_*, terminateInfo_*)
s32 Knife_getSaveBuffer(void);
extern u8 data_021271cc[];
extern u8 data_021271d4[];
extern u8 data_0212c75c[];
extern const u8 data_020ce4d0[];
extern u8 data_0212c508;
extern u8 data_0212c5ac;
extern u8 data_021349c0[];
extern u8 data_0212c500[];
extern u8 data_0212c4dc;
extern u8 data_0212720c[];
extern u8 data_02127214[];

// Menu main loop calls (dsd names; signatures from the disassembly)
extern "C" {
void OS_WaitVBlankIntr(void);
void Menu_Redraw(MenuWork *menu);
void func_020bd128(MenuWork *menu, s32 a);
s32 func_020bd474(MenuWork *menu, void *event);
s32 func_020bd830(MenuWork *menu);
s32 func_020bd968(MenuWork *menu);

void func_020be9f0(void *obj);
void func_020beb00(void *obj, MenuEvent *event);
void func_020be244(MenuWork *menu);
}
// Menu input handlers (C++ names from original_names.tsv)
s32 Menu_HandleInputB(MenuWork *menu, MenuInput *input);
s32 Menu_HandleInput(MenuWork *menu, MenuInput *input);

// Menu redraw calls (dsd names; the signatures follow the calls in Menu_Redraw)
extern "C" {
void func_020bed14(void *obj);
s32 func_020be66c(void *obj, u8 *flag);
void func_020b86f4(void *obj, s32 value);
void func_020b895c(void *obj, s32 value);
void func_020be798(void *obj);
void func_020b8760(void *obj);
void func_020b8964(void *obj, s32 value);
void func_020bacb8(void *obj);
void DC_FlushRange(void *base, u32 size);
}

// Object with two virtual slots; slot 1 (offset 4) is called with two output pointers
class MenuVirtualObj {
public:
    virtual void slot0(void);
    virtual void slot1(void *a, void *b);
};

#endif
