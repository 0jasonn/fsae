#include "engine/functions.h"

// Entry of the list of extra transfers queued for the next CgTrans.
typedef struct CgTransferEntry {
    /* 00 */ const void *source;
    /* 04 */ void *dest;
    /* 08 */ u32 size;
} CgTransferEntry;

extern u32 data_02134904; // palette slots to upload from the translated palette (data_02135da0), 0 when none
extern u32 data_02134918; // palette slots to upload from the plain palette (data_021355a0)
extern u16 data_021355a0[];
extern u16 data_02135da0[];
extern u8 data_02134890; // number of queued transfers
extern CgTransferEntry data_02134894[];

// CgTrans (0x02029dd8): uploads the changed palette slots to the BG palette memory (16 colours per slot) and runs the
// queued transfers.
void CgTrans(void) {
    u16 *source;
    u16 *dest = (u16 *)0x05000000;
    u32 mask = data_02134904;
    u32 size;
    u8 i;

    if (mask != 0) {
        source = data_02135da0;
    } else {
        mask = data_02134918;
        source = data_021355a0;
    }
    if (mask != 0) {
        size = 0x20;
        do {
            if (mask & 1) {
                MIi_CpuCopyFast(source, dest, size);
            }
            source += 0x10;
            dest += 0x10;
            mask >>= 1;
        } while (mask != 0);
    }
    data_02134918 = 0;
    data_02134904 = 0;
    for (i = 0; i < data_02134890; i++) {
        MIi_CpuCopyFast(data_02134894[i].source, data_02134894[i].dest, data_02134894[i].size);
    }
    data_02134890 = 0;
}
