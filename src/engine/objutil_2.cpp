#include "engine/functions.h"
#include "engine/common_d.h"
#include "engine/player.h"
#include "global.h"

extern u8 objAffineSet[];

ARM void ObjAffineSet2(const KnifeObjAffineSrcData *src, Entity *e) {
    u8 *base = objAffineSet + (e->spriteSettings.b24 >> 1) * 0x20;
    u8 *srcRow;
    u8 *dstRow;
    func_02083000(src, base);
    base = objAffineSet + (e->spriteSettings.b24 >> 1) * 0x20;
    srcRow = base + 6;
    dstRow = srcRow + 0x400;
    *(u16 *)dstRow = *(u16 *)(base + 6);
    *(u16 *)(dstRow + 8) = *(u16 *)(srcRow + 8);
    *(u16 *)(dstRow + 0x10) = *(u16 *)(srcRow + 0x10);
    *(u16 *)(dstRow + 0x18) = *(u16 *)(srcRow + 0x18);
}
