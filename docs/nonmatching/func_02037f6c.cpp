// Boss at 0x02036ca4. Attack selection from the last three attacks in unk_7c. Register allocation
// differs around the counts[] increments (history in r1 vs lr).

ARM extern "C" void func_02037f6c(Entity *e) {
    u8 counts[4];
    u8 history = V(e)->unk_7c;
    u8 choice = 0;
    counts[3] = 0;
    counts[2] = 0;
    counts[1] = 0;
    counts[0] = 0;
    counts[history & 3]++;
    counts[(history >> 2) & 3]++;
    counts[(history >> 4) & 3]++;
    if (counts[1] != 0) {
        if (counts[2] == 0) {
            choice = 1;
        } else if (counts[3] == 0) {
            choice = 2;
        } else {
            choice = func_0208455c() % 3;
        }
    }
    switch (choice) {
        case 0:
            e->unk_14 = 0xe;
            func_020859e0(e, 1);
            func_02085f80(0xb2);
            break;
        case 1:
            e->unk_14 = 0x17;
            e->unk_17 = 0x3c;
            break;
        case 2:
            e->unk_14 = 0x1e;
            e->unk_17 = 0x3c;
            break;
    }
    V(e)->unk_7c = (V(e)->unk_7c << 2) | (choice + 1);
    e->unk_18 = 3;
}

