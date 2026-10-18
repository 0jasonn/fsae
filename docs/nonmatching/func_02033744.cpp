// Belongs to object_02033708.cpp (uses its Vars_02033708). Same instructions as the original but
// scheduled/register-allocated differently; statement order permutations did not fix it.

ARM extern "C" void func_02033744(Entity *e) {
    u8 side = V(e)->unk_75;
    e->unk_14 = 1;
    e->unk_17 = 0x20;
    e->unk_1c.b0 = 1;
    e->unk_0c = 0x80;
    e->unk_30.HALF.HI += data_020d0eba[side];
    e->unk_1a = 1;
    e->unk_48 = data_020d0ef2;
    e->unk_5e.b0 = 0;
    e->unk_2b = ((side ^ 1) << 4) + 8;
    if (data_021348b8[side] != 0) {
        data_021348b8[side] = 0;
    }
    func_020859e0(e, V(e)->unk_75 + 1);
}

