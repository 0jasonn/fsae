#ifndef KNIFE_APP_TWL_H
#define KNIFE_APP_TWL_H

// Declarations used by the TWL boot code (twlInit and knifeExitCallback) that are not in
// engine/functions.h yet. The reviewer moves the shared ones there.
//
// twlInit is the last of the TWL boot functions (twlInitVRAM, twlInitAgb, twlInitSubDisplay live
// in src/knife/app/twl.cpp). It turns the display off, resets the display and touch-panel control
// registers, loads the calibration data, initialises the IRQ/VBlank and the TWL display setup, and
// registers knifeExitCallback as the exit callback (data_02171e2c).

#include "types.h"

// TWL boot globals (shared with src/game/resource.cpp and src/engine/callbackset.cpp, which use
// data_02171e20[0] as the ResourceCtrl callback slot).
extern u32 data_02171e20[]; // [0] callback, [1] exit flag, [2] byte flag, [3] exit callback fn, [4] param
extern u32 data_02171e2c;   // 16-byte exit-callback object at data_02171e20 + 0xc


// Calls made by twlInit / knifeExitCallback (TwlSDK or dsd names, C linkage).
extern "C" {
void twlInit(void);                 // plain (unmangled) symbol in symbols.txt
void Os_InitCommonWrap(void);
void func_0218a804(void *exitInfo);  // target outside the ARM9 image (module:none in relocs.txt)
}

// C++-linkage functions (mangled symbols in symbols.txt).
void twlInitVRAM(void);             // _Z11twlInitVRAMv
void twlInitAgb(void);              // _Z10twlInitAgbv
void twlInitSubDisplay(void);       // _Z17twlInitSubDisplayv
void knifeExitCallback(void *arg);  // _Z17knifeExitCallbackPv
u8 Knife_GetManualFlag(void);       // _Z19Knife_GetManualFlagv

#endif
