#include "engine/functions.h"
#include "game/stageseldecls.h"

// effect_char_load, 0x02078c80. Loads the graphics of stage select character index (first call sets up the
// buffer pointers), then creates the character's stage select objects and plays its sound unless mode is nonzero.
ARM void effect_char_load(u8 index, int mode) {
    if ((data_02171d58.loadFlags & 1) == 0) {
        *(u32 *)(data_02116720 + 0xa4) = (u32)data_02148fa0 + 0x2000;
        *(u32 *)(data_02116720 + 0xac) = (u32)data_02140fa0 + 0x4000;
        *(u32 *)(data_02116720 + 0xbc) = (u32)data_02148fa0 + 0x4000;
        *(u32 *)(data_02116720 + 0xcc) = (u32)data_02150fa0 + 0x4000;
        data_02171d58.loadFlags |= 1;
    }
    func_020845b0(0x6404000, (void *)data_021167c4[index * 2], (u16)data_021167c4[index * 2 + 1]);
    if (mode == 0) {
        SoundReq(0x80020000);
    }
    switch (index) {
    case 0:
        ssel_char_scr(index);
        GetSetWork(0x46, 8, index);
        GetSetWork(0x46, 9, index);
        if (mode == 0) {
            SoundReq(0x1b8);
        }
        return;
    case 1: {
        u8 part = 0x13;
        ssel_char_scr(index);
        GetSetWork(0x46, 0xa, index);
        GetSetWork(0x46, 0xe, index);
        GetSetWork(0x46, part, index);
        if (mode == 0) {
            SoundReq(0x1c8 - part);
        }
        return;
    }
    case 2:
        ssel_char_scr(index);
        GetSetWork(0x46, 0xc, index);
        GetSetWork(0x46, 0x10, index);
        if (mode == 0) {
            SoundReq(0x1b4);
        }
        return;
    case 3: {
        u8 part = 0x12;
        ssel_char_scr(index);
        GetSetWork(0x46, 0xd, index);
        GetSetWork(0x46, 0xf, index);
        GetSetWork(0x46, part, index);
        if (mode == 0) {
            SoundReq(part + 0x1a4);
        }
        return;
    }
    case 4:
        if ((enemyTypeFlags[localPlayerIndex].flags & 0x800) != 0) {
            data_02171d58.unk_10 = 0;
            GetSetWork(0x46, 0x16, index);
            GetSetWork(0x46, 0x21, 0);
        }
        if (mode == 0) {
            SoundReq(0x1ea);
        }
        return;
    case 5:
        ssel_char_scr(index);
        if ((enemyTypeFlags[localPlayerIndex].flags & 0x8000) != 0) {
            GetSetWork(0x46, 0x17, index);
            GetSetWork(0x46, 0x21, 1);
        }
        if (mode == 0) {
            SoundReq((Random() & 3) + 0x1b4);
        }
        return;
    case 6: {
        u8 part = 0x21;
        ssel_char_scr(index);
        GetSetWork(0x46, 0x11, index);
        GetSetWork(0x46, part, 2);
        if (mode == 0) {
            SoundReq(0x1d8 - part);
        }
        return;
    }
    }
}
