#include "engine/functions.h"
#include "global.h"
#include "ui/message.h"

extern u8 data_0217d530[];

// telopString (0x0204aa84): writes one line of telop text (21 tiles) at dst: blank tiles (0xf) when the line index has
// no start code, else each tile is the running code (starting at data_0217d530[index]) plus the cell byte of
// that column in the high byte.
void telopString(u16 *tiles, u8 index) {
    int count;
    u32 code;
    u8 i;
    u8 ch;

    count = 0x15;
    code = data_0217d530[index];
    if (code == 0) {
        do {
            *tiles++ = 0xf;
            count--;
        } while (count > 0);
        return;
    }
    i = 0;
    do {
        ch = telopBox.cellRows[index][i];
        i++;
        *tiles++ = (u16)(code | (ch << 8));
        code = (u16)(code + 1);
        count--;
    } while (count > 0);
}
