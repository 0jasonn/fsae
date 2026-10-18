// Boss at 0x02036ca4. Same ldrsb+and #0xff on unk_7d as func_020379d8.

ARM extern "C" void func_02038414(Entity *e) {
    u16 t = V(e)->unk_6e;
    V(e)->unk_73 += (u8)V(e)->unk_7d;
    V(e)->unk_72 = ((data_020d7e58[t] << 5) >> 8) + 0x20;
    V(e)->unk_6e = (t + 1) & 0x7f;
}

