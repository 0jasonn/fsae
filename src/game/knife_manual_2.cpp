#include "engine/functions.h"
#include "global.h"
#include "game/g_knife_manual.h"

// Functions in this file (original names from the debug build):
//   Knife_RunMenuWrapper, Knife_ForwardMenuWrapper (plain C functions, tail calls into the menu code)

extern "C" void Knife_RunMenuWrapper(void);
extern "C" void Knife_ForwardMenuWrapper(void);

// Knife_RunMenuWrapper (0x020c7e28): runs the menu wrapper of the manual mode
ARM void Knife_RunMenuWrapper(void) {
    Menu_RunFromWrapper((MenuWrapper *)&data_0218704c);
}

// Knife_ForwardMenuWrapper (0x020c7e3c): forwards the manual wrapper to func_020bf06c
ARM void Knife_ForwardMenuWrapper(void) {
    func_020bf06c((MenuWrapper *)&data_0218704c, data_02187050);
}
