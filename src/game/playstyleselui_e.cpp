#include "engine/functions.h"
#include "global.h"
#include "game/playstyleselui_e.h"

// Functions in this file (plain names from the debug build, C linkage):
//   playStyleSelUIView_leave (0x020aacfc): leave slot 4, only removes the title dialog
//   playStyleSelUIView_vfunc2 (0x020ab520): empty slot 2

// playStyleSelUIView leave (0x020aacfc): tail-calls knife_title_dialogDelete
ARM void playStyleSelUIView_leave(void *self) {
    knife_title_dialogDelete();
}
