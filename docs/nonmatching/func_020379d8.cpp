// Boss at 0x02036ca4 (Vars_02036ca4). The original loads unk_7d with ldrsb and masks it with
// and #0xff before adding to unk_73; every C form tried loads it with ldrb instead.

ARM extern "C" void func_020379d8(Entity *e) {
    func_02085980(e);
    V(e)->unk_73 += (u8)V(e)->unk_7d;
    if (V(e)->unk_6e < 0x20) {
        V(e)->unk_6e++;
        V(e)->unk_72 = 0x20 - ((data_020d7e58[V(e)->unk_6e] << 5) >> 8);
        return;
    }
    if (--e->unk_17 != 0) {
        return;
    }
    V(e)->unk_70 = 0xff;
    e->unk_14 = 0x1d;
    e->unk_17 = 0x3c;
    func_02085f80(0x9f);
}

