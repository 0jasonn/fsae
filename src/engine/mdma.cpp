#include "engine/functions.h"
#include "global.h"
#include "object/tama11.h"

// mdma module, 0x02080d18 to 0x02080e58. Command records in data_0212ccb0: a 4-byte source, a 4-byte destination and a
// 2-byte size (little endian), 10 bytes in all; each function takes a record and returns the record after it.
//   mdma (0x02080d18): copies the block with MIi_CpuCopyFast.
//   MdmaCheck (0x02080d70): true while the write cursor of the current half is below the end of that half.
//   mdma_zMalloc (0x02080da8): copies the block, then frees its source with zFree.
//   mdma_forComp (0x02080e0c): decompresses an LZ16 block into the destination.

void zFree(void *block);
extern "C" void MI_UncompressLZ16(const void *src, void *dst);
extern u8 data_0212c4c8;
extern u32 data_0212c56c;
extern u8 data_0212ccb0[];

// mdma (0x02080d18)
ARM unsigned char *mdma(unsigned char *record) {
    u32 src;
    u32 dst;
    u32 size;

    src = record[0] + (record[1] << 8) + (record[2] << 16) + (record[3] << 24);
    dst = record[4] + (record[5] << 8) + (record[6] << 16) + (record[7] << 24);
    size = record[8] + (record[9] << 8);
    MIi_CpuCopyFast((const void *)src, (void *)dst, size);
    return record + 10;
}

// MdmaCheck (0x02080d70)
ARM BOOL MdmaCheck(void) {
    return data_0212c56c < (u32)(data_0212ccb0 + (data_0212c4c8 << 8) + 0xf6);
}

// mdma_zMalloc (0x02080da8)
ARM unsigned char *mdma_zMalloc(unsigned char *record) {
    u32 src;
    u32 dst;
    u32 size;

    src = record[0] + (record[1] << 8) + (record[2] << 16) + (record[3] << 24);
    dst = record[4] + (record[5] << 8) + (record[6] << 16) + (record[7] << 24);
    size = record[8] + (record[9] << 8);
    MIi_CpuCopyFast((const void *)src, (void *)dst, size);
    zFree((void *)src);
    return record + 10;
}

// mdma_forComp (0x02080e0c)
ARM unsigned char *mdma_forComp(unsigned char *record) {
    u32 src;
    u32 dst;

    src = record[0] + (record[1] << 8) + (record[2] << 16) + (record[3] << 24);
    dst = record[4] + (record[5] << 8) + (record[6] << 16) + (record[7] << 24);
    MI_UncompressLZ16((const void *)src, (void *)dst);
    return record + 10;
}
