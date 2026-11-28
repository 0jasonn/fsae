#include "global.h"
#include "types.h"
#include "sdk/fatfs/fatfs.h"
#include "engine/functions.h"
#include "sdk/pxi/pxi_fifo.h"
#include "sdk/card/card.h"
#include "sdk/os/dc_cache.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/fatfs/stdconv_table_wrap_api.h"
#include "sdk/std/std_string.h"

void FATFSi_CopyString(char *dst, const char *src, s32 size) {
    STD_CopyLString(dst, src, size);
    dst[(u32)(size - 1)] = 0;
}

void FATFSi_ConvertArcnameToSjis(char *dst, const u16 *src) {
    s32 i;

    i = 0;
    while (i < 0xf && src[i] != 0 && src[i] != 0x3a) {
        dst[i] = src[i];
        i++;
    }
    if (i < 0xf) {
        dst[i] = ':';
        i++;
    }
    dst[i] = 0;
}

void FATFSi_CopyUnicodeString(u16 *dst, const u16 *src, s32 size) {
    u16 c;
    s32 i;

    i = 0;
    while (i < size - 1 && (c = src[i]) != 0) {
        dst[i] = c;
        i++;
    }
    if (size > 0) {
        dst[i] = 0;
    }
}
