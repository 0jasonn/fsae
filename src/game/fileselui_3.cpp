#include "engine/functions.h"
#include "global.h"
#include "game/fileselui.h"

// Functions in this file (original names from the debug build):
//   fileSelUIViewCtrl_clearOamCount (0x020ad954, no debug name: clears the OAM counter),
//   fileSelUIViewCtrl::addOamEntry(unsigned char) (0x020ad964)

// fileSelUIViewCtrl_clearOamCount (0x020ad954): no debug name; sets the OAM counter to zero
ARM void fileSelUIViewCtrl_clearOamCount(FileSelUIViewCtrl *self) {
    self->oamCount = 0;
}

// fileSelUIViewCtrl::addOamEntry(unsigned char) (0x020ad964): adds the OAM entries of one list entry
ARM void fileSelUIViewCtrl_addOamEntry_0ad964(FileSelUIViewCtrl *self, u8 index) {
    self->oamCount += (u16)addOamUiObj((u32)self->oamBuffer, 0x40, &self->uiObjects[index]);
}
