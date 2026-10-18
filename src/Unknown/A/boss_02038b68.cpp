#include "Unknown/A/Boss_02038544.hpp"
#include "global.h"

ARM extern "C" void func_02038b68(Entity *e) {
    e->unk_14++;
    e->unk_17 = (func_0208455c() & 0x30) + 0x3c;
    e->unk_2b = func_0208455c() & 0x18;
    u8 anim = func_02045aa0();
    if (anim == e->unk_2a) {
        return;
    }
    e->unk_2a = anim;
    func_020859e0(e, anim);
}
