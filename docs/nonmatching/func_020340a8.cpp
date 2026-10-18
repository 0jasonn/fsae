// Object at 0x02033708 (Vars_02033708, Vars_Lock). Arms of the if are tail-merged differently and
// register allocation differs; several expression forms tried.

ARM extern "C" void func_020340a8(Entity *e) {
    Entity *lock = V(e)->unk_7c;
    if (V(e)->unk_75 != 0) {
        V(e)->unk_72 = e->unk_30.HALF.HI - V(e)->unk_70;
    } else {
        V(e)->unk_72 = V(e)->unk_70 - e->unk_30.HALF.HI;
    }
    u16 mask;
    if (e->unk_54->unk_14 == 4) {
        VL(lock)->unk_7c -= (u32)((V(e)->unk_72 - V(e)->unk_73) << 14) >> 16;
        mask = 0xfffc;
    } else {
        VL(lock)->unk_7c -= (u32)((V(e)->unk_72 - V(e)->unk_73) << 13) >> 16;
        mask = 0xfff8;
    }
    V(e)->unk_73 = V(e)->unk_72 & mask;
}

