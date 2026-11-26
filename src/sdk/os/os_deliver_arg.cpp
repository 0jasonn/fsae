#include "global.h"
#include "types.h"
#include "sdk/os/pair_block.h"

// Start of main RAM (0x02000000): the byte at +9 has bit 1 set when a deliver argument was passed.
typedef struct MainRamHeader {
    u8 unk_00[9];
    u8 deliverFlags;
} MainRamHeader;

BOOL OS_IsValidDeliverArg(void) {
    MainRamHeader *header = (MainRamHeader *)0x02000000;
    if ((header->deliverFlags & 2) != 0) {
        return TRUE;
    }
    return FALSE;
}
