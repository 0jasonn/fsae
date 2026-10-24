#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (provisional name for a func_ address):
//   Knife_Comm_selectDataTable (0x020ae540): Knife_Comm_selectDataTable, returns one of two rodata tables by the flag

extern "C" const void *Knife_Comm_selectDataTable(s32 unused, s32 flag);
extern const u8 data_020dec1c[];
extern const u8 data_020deca0[];

// Knife_Comm_selectDataTable (0x020ae540): returns data_020deca0 when flag is set, data_020dec1c otherwise
ARM const void *Knife_Comm_selectDataTable(s32 unused, s32 flag) {
    const void *table;

    table = data_020dec1c;
    if (flag != 0) {
        table = data_020deca0;
    }
    return table;
}
