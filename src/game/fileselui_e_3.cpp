#include "engine/functions.h"
#include "global.h"
#include "game/fileselui_e.h"

// Functions in this file (plain names from the debug build, C linkage):
//   fileSelUIView_errorFileInit (0x020a88a8), fileSelUIView_getText (0x020a8d78), fileSelUIView_vfunc2 (0x020a8f7c)

extern "C" void *Knife_Message_getCESObject_021770b4(void);
extern "C" void clearSaveData(u8 index);
extern "C" void fileSelUIView_errorFileInit(void *self);
void Knife_InitialSaveFile(u8 index);
void Knife_mediaWrite(void);
extern u8 data_021350b0[];

// fileSelUIView slot 2 (0x020a8f7c): empty
ARM void fileSelUIView_vfunc2(void *self) {
}
