#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   SearchCellTbl

// Looks key up in a list of (key, value) pairs ending with 0xffff; returns the value or 0xffff when not found
ARM u16 SearchCellTbl(const u16 *table, u16 key) {
    u16 result;

    result = 0xffff;
    do {
        if (table[0] == key) {
            result = table[1];
            break;
        }
        table += 2;
    } while (table[0] != 0xffff);
    return result;
}
