#include "engine/functions.h"
#include "global.h"
#include "types.h"

// work21_clear: function Work21_clear (0x020b7080), matching. It clears a 0x21 byte record: eight halfwords from +0,
// a word at +0x10, halfwords at +0x14 and +0x16, words at +0x18 and +0x1c and a byte at +0x20.

typedef struct Work21 {
    u16 h00;      // 0x00
    u16 h02;      // 0x02
    u16 h04;      // 0x04
    u16 h06;      // 0x06
    u16 h08;      // 0x08
    u16 h0a;      // 0x0a
    u16 h0c;      // 0x0c
    u16 h0e;      // 0x0e
    u32 w10;      // 0x10
    u16 h14;      // 0x14
    u16 h16;      // 0x16
    u32 w18;      // 0x18
    u32 w1c;      // 0x1c
    u8 b20;       // 0x20
} Work21;

// Work21_clear(self) (0x020b7080, provisional name): zeroes the record
extern "C" void Work21_clear(void *self);
ARM void Work21_clear(void *self) {
    Work21 *work;

    work = (Work21 *)self;
    work->h00 = 0;
    work->h02 = 0;
    work->h04 = 0;
    work->h06 = 0;
    work->h08 = 0;
    work->h0a = 0;
    work->h0c = 0;
    work->h0e = 0;
    work->w10 = 0;
    work->h14 = 0;
    work->h16 = 0;
    work->w18 = 0;
    work->w1c = 0;
    work->b20 = 0;
}
