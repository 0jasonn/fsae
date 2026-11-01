#include "engine/functions.h"
#include "engine/str_format.h"
#include "game/subtask_d.h"
#include "global.h"
#include "types.h"

// hex_ascii_chg0(int, int, unsigned long, void*) (0x0209ad3c): clears the 16-byte buffer dst, formats the value c
// into it with Str_Sprintf and returns the number of characters written. The format is one of two templates copied
// from rodata ("%2d" and "%02d") with the width digit b patched in, or a fixed "%d" / "%x" for modes 2 and 6.

extern "C" void *FindByteForward(void *buf, u8 value, u32 size);

extern "C" int hex_ascii_chg0(int a, int b, unsigned long c, void *d);
int hex_ascii_chg0(int a, int b, unsigned long c, void *d) {
    char fmtWide[5] = "%02d";
    char fmtNarrow[4] = "%2d";
    int len;

    MI_CpuFill8(d, 0, 0x10);
    switch (a) {
    case 0:
        fmtWide[2] = b + '0';
        Str_Sprintf((u8 *)d, (const u8 *)fmtWide, c);
        break;
    case 1:
        fmtNarrow[1] = b + '0';
        Str_Sprintf((u8 *)d, (const u8 *)fmtNarrow, c);
        break;
    case 2:
        Str_Sprintf((u8 *)d, (const u8 *)"%d", c);
        break;
    case 4:
        fmtWide[2] = b + '0';
        fmtWide[3] = 'x';
        Str_Sprintf((u8 *)d, (const u8 *)fmtWide, c);
        break;
    case 5:
        fmtNarrow[1] = b + '0';
        fmtNarrow[2] = 'x';
        Str_Sprintf((u8 *)d, (const u8 *)fmtNarrow, c);
        break;
    case 6:
        Str_Sprintf((u8 *)d, (const u8 *)"%x", c);
        break;
    }
    len = (u8 *)FindByteForward(d, 0, 0x10) - (u8 *)d;
    return len;
}
