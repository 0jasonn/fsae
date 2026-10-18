// Belongs between func_02031084 and func_02031304 (boss at 0x02030a14), uses that file's Vars_Boss.
// Only difference: the original does `sub r1, r1, #1` (table index) after storing unk_17 and unk_73,
// this version schedules it before both stores. Every DSi compiler version gives the same output.

ARM extern "C" void func_0203120c(Entity *e) {
    func_02085980(e);
    if (e->unk_29 == 0) {
        return;
    }
    e->unk_14 = 4;
    if ((e->unk_0b = func_0208455c() & 1)) {
        e->unk_2b = 0x10;
    } else {
        e->unk_2b = 0;
    }
    V(e)->unk_73 = 1;
    e->unk_17 = 1;
    const u8 *table = data_020f263c[e->unk_0a - 1];
    e->unk_18 = table[func_0208455c() & 3];
    e->unk_0c = 0x100;
    e->unk_10 = 0x30000;
    func_020859e0(e, (e->unk_0a - 1) * 10 + 1);
    if (e->unk_0a == 2) {
        V(e)->unk_79 = 0;
        e->unk_3c &= 0x7f;
        e->unk_1c.b0 = 0;
        func_02032910(e);
        return;
    }
    if (e->unk_0a == 3) {
        V(e)->unk_78 = func_02085608();
        func_02076fe0(0xa1);
    }
    func_02076fe0(0x31);
}

