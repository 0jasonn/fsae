#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   historyCheck, pasthistoryCheck, checkSingleErrorFrame, checkSingleErrorParts

// Recent-entry table (32 pointers) and past-entry table, both in bss
extern void *data_0216f834[];
extern void *data_0216f8b4[];
// Pairs of (key, value) u16 entries used by the single error checks
extern const u16 data_02103cd4[];
extern const u16 data_02103cd8[];

// Adds entry to the recent list unless it is already there; returns 1 when it was added
ARM int historyCheck(void *entry) {
    u8 i;
    u8 count;

    i = 0;
    count = 0;
    do {
        if (data_0216f834[i] == entry) {
            return 0;
        }
        if (data_0216f834[i] == 0) {
            break;
        }
        i = (u8)(i + 1);
        count = (u8)(count + 1);
    } while (i < 0x20);
    if (count < 0x20) {
        data_0216f834[count] = entry;
    }
    return 1;
}

// Returns 0 when entry is in the past list, 1 when the list has room left, 0 when it is full
ARM int pasthistoryCheck(void *entry) {
    u8 i;

    i = 0;
    do {
        if (data_0216f8b4[i] == entry) {
            return 0;
        }
        if (data_0216f8b4[i] == 0) {
            return 1;
        }
        i = (u8)(i + 1);
    } while (i < 0x20);
    return 0;
}

// Returns 0 when (frame, value) is one of the two listed pairs, 1 otherwise
ARM int checkSingleErrorFrame(u8 frame, u16 value) {
    u32 i;

    for (i = 0; i < 2; i += 2) {
        if (frame == data_02103cd4[i] && value == data_02103cd4[i + 1]) {
            return 0;
        }
    }
    return 1;
}

// Same as checkSingleErrorFrame for the parts table
ARM int checkSingleErrorParts(u8 part, u16 value) {
    u32 i;

    for (i = 0; i < 2; i += 2) {
        if (part == data_02103cd8[i] && value == data_02103cd8[i + 1]) {
            return 0;
        }
    }
    return 1;
}
