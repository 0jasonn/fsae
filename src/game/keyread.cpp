#include "engine/functions.h"
#include "game/keyread.h"

// KeyRead (0x0202a190): reads the key registers (the console keys and the X/Y buttons), removes impossible
// opposite directions (up with down, left with right) and keeps the keys that are held, newly pressed and repeating.
void KeyRead(void) {
    u16 keys = ((*(volatile u16 *)0x04000130 | *(volatile u16 *)0x02ffffa8) ^ 0x2fff) & 0x2fff;

    keys = keys & ~((keys & 0x40) << 1) & ~((keys & 0x20) >> 1);
    if (((*(volatile u16 *)0x02ffffa8 & 0x8000) >> 15) != 0) {
        keys = 0;
    }
    keys &= 0x2fff;
    data_0212c510 = keys & ~data_0212c514;
    if (keys == data_0212c514) {
        data_0212c51c--;
        if (data_0212c51c == 0) {
            data_0212c518 = keys;
            data_0212c51c = 4;
        } else {
            data_0212c518 = 0;
        }
    } else {
        data_0212c51c = 0x14;
        data_0212c518 = data_0212c510;
    }
    data_0212c514 = keys;
    data_0212c5d4.unk_04 = 0;
    data_0212c5d4.unk_10 = 0;
    data_0212c5d4.unk_00 = 0;
    data_0212c5d4.unk_02 = 0;
}

// KeyRepeat (0x0202a2a0): counts how long each direction key is held and, after 30 frames, reports it as pressed
// again every 8 frames (the counter restarts at 22).
void KeyRepeat(void) {
    u16 held = data_0212c514;

    if (held & 0x40) {
        data_0212c548[0] = data_0212c548[0] + 1;
    } else {
        data_0212c548[0] = 0;
    }
    if (held & 0x10) {
        data_0212c548[1] = data_0212c548[1] + 1;
    } else {
        data_0212c548[1] = 0;
    }
    if (held & 0x80) {
        data_0212c548[2] = data_0212c548[2] + 1;
    } else {
        data_0212c548[2] = 0;
    }
    if (held & 0x20) {
        data_0212c548[3] = data_0212c548[3] + 1;
    } else {
        data_0212c548[3] = 0;
    }
    if (data_0212c548[0] >= 0x1e) {
        data_0212c510 |= 0x40;
        data_0212c548[0] = 0x16;
    }
    if (data_0212c548[1] >= 0x1e) {
        data_0212c510 |= 0x10;
        data_0212c548[1] = 0x16;
    }
    if (data_0212c548[2] >= 0x1e) {
        data_0212c510 |= 0x80;
        data_0212c548[2] = 0x16;
    }
    if (data_0212c548[3] >= 0x1e) {
        data_0212c510 |= 0x20;
        data_0212c548[3] = 0x16;
    }
}
