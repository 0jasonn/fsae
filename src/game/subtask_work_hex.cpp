#include "engine/functions.h"
#include "global.h"

// subtask_hex_ascii_work (0x0209ae98): calls hex_ascii_chg0 with the work block of the subtask (pointer at data_0217d23c + 0x10c,
// buffer at +0x938) as its last argument. The original tail-calls hex_ascii_chg0.
extern u8 data_0217d23c[];
extern "C" void hex_ascii_chg0(int a, int b, unsigned long c, void *d);

extern "C" void subtask_hex_ascii_work(int a, int b, unsigned long c);
ARM void subtask_hex_ascii_work(int a, int b, unsigned long c) {
    u8 *work = *(u8 **)(data_0217d23c + 0x10c);

    hex_ascii_chg0(a, b, c, work + 0x938);
}
