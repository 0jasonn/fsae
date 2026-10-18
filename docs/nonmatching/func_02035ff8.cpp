// Enemy at 0x020347dc. Only difference: the original masks the animation (and r2, r1, #7) before
// loading unk_2a, this version after.

ARM extern "C" void func_02035ff8(Entity *e) {
    e->unk_2b = func_0204fdf0(e->unk_54, e);
    int anim = ((e->unk_2b + 2) >> 2) & 7;
    if (e->unk_2a != anim) {
        e->unk_2a = anim;
        func_020859e0(e, anim + 0x14);
    }
    func_0204fd40(e);
    e->unk_2b = (e->unk_2b + 8) & 0x1f;
    func_0204fd40(e);
}

