#include "engine/common_d.h"
#include "engine/player.h"
#include "global.h"

void func_02083000(Entity *a, u8 *base);
extern u8 data_0212dd90[];

ARM void ObjAffineSet2(Entity *a, Entity *e) {
    u8 *base = data_0212dd90 + (e->spriteSettings.b24 >> 1) * 0x20;
    u8 *q;
    u8 *d;
    func_02083000(a, base);
    base = data_0212dd90 + (e->spriteSettings.b24 >> 1) * 0x20;
    q = base + 6;
    d = q + 0x400;
    *(u16 *)d = *(u16 *)(base + 6);
    *(u16 *)(d + 8) = *(u16 *)(q + 8);
    *(u16 *)(d + 0x10) = *(u16 *)(q + 0x10);
    *(u16 *)(d + 0x18) = *(u16 *)(q + 0x18);
}
