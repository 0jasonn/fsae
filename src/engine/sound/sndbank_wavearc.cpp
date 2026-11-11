#include "ui/sndwavearc.h"

// SndBank_AcquireWaveArc (0x020c1268): returns the wave archive of the table entry when it is cached. Otherwise it
// reads the archive header to learn the entry count, makes a record in the heap, reads the archive into it, copies
// (the header buffer is addressed once through data_021848b0.hdr and once as data_021848b4: two literals in the ROM)
// the entry block behind the entries, clears it, flushes the cache and (when flag is set) caches the result.
void *SndBank_AcquireWaveArc(s32 index, void *record, s32 flag) {
    void *data;
    s32 doubleSize;
    SndWaveArc *arc;
    s32 entrySize;
    s32 bytesRead;

    arc = (SndWaveArc *)SndTable_GetWord14(index);
    if (arc == 0) {
        data = 0;
        if (SndTable_ReadBlock(index, data_021848b0.hdr, 0x3c, 0) != 0x3c) {
            return 0;
        }
        entrySize = data_021848b4[0x38 / 4] << 2;
        doubleSize = entrySize << 1;
        if (record == 0) {
            return 0;
        }
        if (flag != 0) {
            data = func_020c05dc();
        }
        arc = (SndWaveArc *)func_020c0b20(record, doubleSize + 0x5c, (void *)SndBank_ReleaseWaveArc, data, index);
        if (arc == 0) {
            return 0;
        }
        data = 0;
        bytesRead = SndTable_ReadBlock(index, arc, entrySize + 0x3c, 0);
        if (bytesRead != entrySize + 0x3c) {
            return 0;
        }
        MI_CpuCopy8(arc->data, arc->data + arc->count * 4, entrySize);
        MI_CpuFill8(arc->data, 0, entrySize);
        DC_StoreRange(arc, doubleSize + 0x3c);
        if (flag != 0) {
            SndTable_SetWord14(index, (u32)arc);
        }
    }
    return arc;
}
