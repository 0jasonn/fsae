#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   RandomSetInit

// Random set records (0x0c bytes each, eight of them)
typedef struct RandomSetWork {
    /* 00 */ u32 unk_00;
    /* 04 */ u16 unk_04;
    /* 06 */ u8 unk_06;
    /* 07 */ u8 unk_07;
    /* 08 */ u8 unk_08[4];
} RandomSetWork;

extern RandomSetWork data_02134ae8[];

// Clears the eight random set records
ARM void RandomSetInit(void) {
    u16 i;

    for (i = 0; i < 8; i++) {
        data_02134ae8[i].unk_00 = 0;
        data_02134ae8[i].unk_04 = 0;
        data_02134ae8[i].unk_06 = 0;
        data_02134ae8[i].unk_07 = 0;
    }
}
