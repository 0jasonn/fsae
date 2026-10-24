#ifndef WIP_D_KNIFE_APP_H
#define WIP_D_KNIFE_APP_H

#include "types.h"

// KnifeApp: the application object. Its first word is the heap pointer of the GzAllocator that init sets up. The
// other members are only used by the functions in knife_app.cpp.
class KnifeApp {
public:
    void init(void);
};

extern "C" {
// Sub-object calls used by the KnifeApp destructor (dsd names)
void Knife_Hud_HudManager_dtor_HudManager_09e004(void *member);
void func_0209a65c(void *member);
}

#endif
