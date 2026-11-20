#include "engine/functions.h"
#include "global.h"
#include "engine/entry_check.h"

#include "engine/com_work.h"
extern u32 opTitleState;

// entry_check (0x02028240): when the low nibble of byte 3 differs from bits 8..11 of opTitleState, sets byte 1 to 4,
// clears byte 2 and copies the nibble to byte 3.
void entry_check(void) {
    u32 level = (opTitleState >> 8) & 0xf;

    if (level != (comWork.status & 0xf)) {
        comWork.phase = 4;
        comWork.counter = 0;
        comWork.status = comWork.status & 0xf;
    }
}
