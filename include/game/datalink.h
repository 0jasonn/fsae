#ifndef WIP_E_DATALINK_H
#define WIP_E_DATALINK_H

#include "engine/functions.h"

// Datalink (the data block of the datalink files): a CRC-16 and the check of a block.
class Datalink {
public:
    static u16 crc(const void *data, u32 size);
    static BOOL verify(const void *data, u32 size);
};

// Reader of a datalink block: the block is checked by Datalink::verify, the entries follow the 16-byte header.
class DatalinkReader {
public:
    BOOL initialize(const void *block, u32 blockSize);
    void finalize(void);
    const void *getDataBuffer(s32 index) const;
    s32 getDataSize(s32 index) const;

    const void *block;  // 0x00
    u32 *table;         // 0x04: the entries (offset and size, 8 bytes each), at block + 0x10
    u32 blockSize;      // 0x08
    u8 initialized;     // 0x0c
};

#endif
