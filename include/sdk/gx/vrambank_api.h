#ifndef SDK_GX_VRAMBANK_API_H
#define SDK_GX_VRAMBANK_API_H

// Functions defined in src/sdk/gx/vrambank*.cpp: each resets the bank record of one use (TwlSDK GX_ResetBankFor*)
// and returns the banks it held.

#include "engine/entity.h"

extern "C" {
u32 Vram_ResetMainBankA(void); // main BG extended palette
u32 Vram_ResetMainBankB(void); // main OBJ extended palette
u32 Vram_ResetBankC(void);     // texture
u32 Vram_ResetBankD(void);     // texture palette
u32 Vram_ResetSubBankA(void);  // sub BG extended palette
u32 Vram_ResetSubBankB(void);  // sub OBJ extended palette
}

#endif
