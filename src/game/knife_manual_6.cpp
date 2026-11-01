#include "engine/functions.h"
#include "global.h"
#include "game/g_knife_manual.h"
#include "game/decls_g.h"
#include "game/knife_power.h"

// Functions in this file (original names from the debug build):
//   Knife::i_initM2dLibrary (0x020c7da0)

// 21-byte configuration block copied from rodata (data_020df1e8) into a local of i_initM2dLibrary
typedef struct KnifeM2dConfig {
    u8 bytes[21];
} KnifeM2dConfig;

extern const KnifeM2dConfig data_020df1e8;

namespace Knife {

// Knife::i_initM2dLibrary() (0x020c7da0): copies the configuration block, builds three slot pointers into
// data_02187070 (8 bytes apart) and passes them with the manual object to the library setup
void i_initM2dLibrary(void) {
    void *slots[3];
    KnifeM2dConfig config;
    s32 i;

    config = data_020df1e8;
    for (i = 0; i < 3; i++) {
        slots[i] = (u8 *)data_02187070 + i * 8;
    }
    Menu_CreateEntryDefault(&data_0218704c, data_02187050, &config, data_021271ac, slots);
}

}

// Functions in this file (original names from the debug build):
//   Knife_RunMenuWrapper, Knife_ForwardMenuWrapper (plain C functions, tail calls into the menu code)

extern "C" void Knife_RunMenuWrapper(void);
extern "C" void Knife_ForwardMenuWrapper(void);

// Knife_RunMenuWrapper (0x020c7e28): runs the menu wrapper of the manual mode
void Knife_RunMenuWrapper(void) {
    Menu_RunFromWrapper((MenuWrapper *)&data_0218704c);
}

// Knife_ForwardMenuWrapper (0x020c7e3c): forwards the manual wrapper to Menu_ReleaseWrapper
void Knife_ForwardMenuWrapper(void) {
    Menu_ReleaseWrapper((MenuWrapper *)&data_0218704c, data_02187050);
}

// Functions in this file (original names from the debug build):
//   Knife::i_postprocManual (0x020c7e58)

namespace Knife {

// Knife::i_postprocManual() (0x020c7e58): frees the three blocks and the single block of the manual object, then
// restores the graphics settings, clears the object and unlocks the sleep state
void i_postprocManual(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (data_0218704c.blocks[i] != 0) {
            i_deallocate(data_0218704c.blocks[i]);
            data_0218704c.blocks[i] = 0;
        }
    }
    if (data_0218704c.block14 != 0) {
        i_deallocate(data_0218704c.block14);
        data_0218704c.block14 = 0;
    }
    m4aEnterManualAlias();
    i_restoreGfxSettings();
    MI_CpuFill8(&data_0218704c, 0, 0x40);
    ((PowerManager *)Knife_GetPowerManager())->unlockSleep();
}

}

// Functions in this file (original names from the debug build):
//   Knife::i_restoreGfxSettings (0x020c7ed4)

namespace Knife {

// Knife::i_restoreGfxSettings() (0x020c7ed4): resets the display and the VRAM banks, sets up the touch panel, the
// wireless icon and the task state, and clears the menu state bytes of the application object
void i_restoreGfxSettings(void) {
    u8 *app;

    func_02012c40();
    GX_DispOff();
    *(u32 *)0x04001000 = *(u32 *)0x04001000 & ~0x10000;
    Vram_SetLcdcBits(0x1ff);
    MIi_CpuClearFast(0, (void *)0x06800000, 0xa4000);
    Vram_DisableBankTail();
    MIi_CpuClearFast(0xc0, (void *)0x07000000, 0x400);
    MIi_CpuClearFast(0, (void *)0x05000000, 0x400);
    MIi_CpuClearFast(0xc0, (void *)0x07000400, 0x400);
    MIi_CpuClearFast(0, (void *)0x05000400, 0x400);
    func_020148f0(1);
    func_02014af4(2);
    GX_SetGraphicsMode(1, 0, 0);
    *(u32 *)0x04000000 = (*(u32 *)0x04000000 & 0xffcfffef) | 0x10;
    Vram_SetBankGroupA(4);
    func_02015120(8);
    TP_Init();
    if (TP_GetUserInfo(data_0212c57c) == 0) {
        OS_Terminate();
    }
    TP_SetCalibrateParam(data_0212c57c);
    app = (u8 *)KnifeApp_getInstance();
    Knife_Comm_WirelessIcon_initialize_16x16_ColorMode(app + 4, 1, 0xf);
    app[0x18] = 1;
    *(u32 *)(app + 0x10) = 0;
    *(u32 *)(app + 0x14) = 0;
    Irq_InitVBlank();
    data_0212c524 = 0;
    DispReset();
    *(u16 *)0x05000000 = 0x6739;
    data_021355a0 = 0x6739;
    ObjWorkPoolClear();
    ObjMoveInit();
    MessageInitialize();
    TelopInitialize();
    ComInitState();
    Task_Chain(7);
    subTask_game_start_reload();
    func_020827a8(3);
    data_0212c4dc = 1;
}

}

// Functions in this file (original names from the debug build):
//   Knife_CheckIndexed (provisional name, returns the result of func_020c2c34 for a clamped index)

// Knife_CheckIndexed (0x020c806c): the index is clamped to at least 1 and passed to func_020c2c34 on data_02187050
s32 Knife_CheckIndexed(s32 a) {
    s32 id;
    s32 r;

    id = a;
    if (id <= 0) {
        id = 1;
    }
    r = func_020c2c34((MenuChecker *)data_02187050, id);
    if (r == 0) {
        return 0;
    }
    return r;
}

// Functions in this file (original names from the debug build):
//   Knife::i_deallocate (0x020c8094), Knife::i_VBlankIntr_OnManual (0x020c80b0), Knife_IrqStub (0x020c8100, empty IRQ stub)

namespace Knife {

// Knife::i_deallocate(void*) (0x020c8094): frees a block through the heap at data_02187050
void i_deallocate(void *block) {
    if (block != 0) {
        Heap_VirtualFree(data_02187050, block);
    }
}

// Knife::i_VBlankIntr_OnManual() (0x020c80b0): saves the context, sets bit 0 of the register at 0x02fe3ff8,
// restores the context and waits until the divider is idle
void i_VBlankIntr_OnManual(void) {
    u8 context[0x1c];

    u32 base;

    CP_SaveContext(context);
    base = (u32)data_02fe0000;
    base += 0x3000;
    *(u32 *)(base + 0xff8) |= 1;
    CPi_RestoreContext(context);
    while (*(volatile u16 *)0x04000280 & 0x8000) {
    }
}

}

// Knife_IrqStub (0x020c8100): empty interrupt stub
extern "C" void Knife_IrqStub(void);
void Knife_IrqStub(void) {
}
