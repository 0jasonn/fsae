#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// Two forwarders to the BG3 screen writers (func_02013d28, func_02013c6c). Their roles are not confirmed yet.

ARM void Menu_Bg3WriteA(s32 a, s32 b, s32 c, s32 d) {
    func_02013d28(a, b, c, d);
}

ARM void Menu_Bg3WriteB(s32 a, s32 b, s32 c, s32 d) {
    func_02013c6c(a, b, c, d);
}
