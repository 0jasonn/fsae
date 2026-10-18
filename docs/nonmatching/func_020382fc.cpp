// Boss at 0x02036ca4. Register allocation differs (index/table/loop counter).

ARM extern "C" void func_020382fc(Entity *e) {
    u32 r = func_0208455c();
    int index = r % 3 + func_020384b8(e) * 4;
    for (u16 i = 0; i < 8; i++) {
        Entity *proj = func_0204bdb8(0x10);
        if (proj != NULL) {
            if (func_02084670(&data_020d1458[index], i)) {
                proj->unk_0a = func_0208455c() % data_0212c7c8.unk_0 + 1;
            } else {
                proj->unk_0a = 0;
            }
            proj->unk_2b = i << 5;
            proj->unk_54 = e;
            func_0205031c(e, proj);
        }
    }
}

