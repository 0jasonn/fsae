#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "game/yousei.h"
#include "game/b_extra.h"

// Yousei demo fade, 0x02081f14 to 0x02082054.
//   yousei_fade (0x02081f14): step 0 counts the timer at data_021349c0+4 down, then starts the fade and moves to step 1;
//   step 1 waits for ZeldaFadeFlagGet, bumps the demo step, sets every player to state 3 and finishes the fade.
//   yousei_msgFinishWait (0x02082008): 1 while any player's message window (bit 12 of data_0212c584) is open.

extern u8 data_0212c4dc; // demo sub-step
extern u8 data_0212c500; // demo step
extern u8 data_021349c0[]; // 16-bit timer at +4
extern u8 data_0212c75c[]; // display block, 16-bit fields at +0, +0x66 and +0x68
extern u16 data_0212c584[];

// yousei_fade (0x02081f14)
ARM void yousei_fade(void) {
    u8 i;

    switch (data_0212c4dc) {
    case 0:
        *(u16 *)(data_021349c0 + 4) = *(u16 *)(data_021349c0 + 4) - 1;
        if (*(u16 *)(data_021349c0 + 4) != 0) {
            return;
        }
        *(u16 *)(data_0212c75c + 0x66) = 0x3f40;
        *(u16 *)(data_0212c75c + 0x68) = 0x70c;
        ZeldaFadeSet(NULL, 1);
        *(u16 *)data_0212c75c = *(u16 *)data_0212c75c | 0x1700;
        data_0212c4dc = data_0212c4dc + 1;
        return;
    case 1:
        if (ZeldaFadeFlagGet() == 0) {
            return;
        }
        data_0212c500 = data_0212c500 + 1;
        data_0212c4dc = 0;
        for (i = 0; i < data_0212c7c8.unk_0; i++) {
            data_0212ceb0[i].state = 3;
        }
        ZeldaFadeFinish();
        return;
    }
}

// yousei_msgFinishWait (0x02082008)
ARM int yousei_msgFinishWait(void) {
    u8 i;

    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        if (data_0212c584[i] & 0x1000) {
            return 1;
        }
    }
    return 0;
}
