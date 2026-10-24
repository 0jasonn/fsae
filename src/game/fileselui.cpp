#include "engine/functions.h"
#include "global.h"
#include "game/fileselui.h"

// fileSelUIViewCtrl::initUIObject (0x020ad020) is the only function of this unit: initialize (0x020ad070) is not done yet

// fileSelUIViewCtrl::initUIObject (0x020ad020): clears the UI object table and initialises every object
ARM void fileSelUIViewCtrl_initUIObject(FileSelUIViewCtrl *self) {
    u32 i;

    self->unk_253c = 0;
    MI_CpuFill8(self->uiObjects, 0, 0x2100);
    for (i = 0; i < 0x60; i++) {
        UIObject_init(&self->uiObjects[i], (u8)i);
    }
}
