// Chain link follow (uses sine table data_020d7e58). Same operations, but the original computes the
// x difference before the scaled offset and allocates registers differently.

ARM extern "C" void func_0203464c(Entity *e, Entity *target, u16 dist) {
    u8 angle = func_02086220(target->unk_30.HALF.HI - e->unk_30.HALF.HI, target->unk_34.HALF.HI - e->unk_34.HALF.HI);
    if (dist < 4) {
        dist = 4;
    }
    s32 offset = (dist * data_020d7e58[angle]) << 8;
    s32 diff = target->unk_30.WORD - e->unk_30.WORD;
    s32 move = diff - offset;
    if (ABS(diff) - ABS(offset) <= 0) {
        move = 0;
    }
    e->unk_30.WORD += move;
    offset = -((dist * data_020d7e58[angle + 0x40]) << 8);
    diff = target->unk_34.WORD - e->unk_34.WORD;
    move = diff - offset;
    if (ABS(diff) - ABS(offset) <= 0) {
        move = 0;
    }
    e->unk_34.WORD += move;
}

