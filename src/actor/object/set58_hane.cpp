#include "engine/functions.h"
#include "global.h"
#include "actor/object/set58.h"

extern void *data_0212c568; // pointer to the 0x6c byte display control block (see game/dispctrl.cpp)

// hane_init (0x0207379c): wing of the set58 scene. Shows the sprite with sprite word field bits 10-11 = 1, sets two
// display registers of the display control block, and starts the affine setup (scale 0x400 x 0x100, angle 0).
void hane_init(Entity *e) {
    set58_actionInit(e);
    e->unk_5e.b0 = 1;
    e->spriteSettings.b0 = 1;
    *(u32 *)&e->spriteSettings = (*(u32 *)&e->spriteSettings & ~0xc00) | 0x400;
    *(u16 *)((u8 *)data_0212c568 + 0x66) = 0xf40;
    *(u16 *)((u8 *)data_0212c568 + 0x68) = 0x809;
    func_02085cf8(e);
    e->speed = 0x400;
    scrollArgs.data[0] = 0x400;
    scrollArgs.data[1] = 0x100;
    scrollArgs.data[2] = 0;
    ObjAffineSet2(&scrollArgs, e);
}
