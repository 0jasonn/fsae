#include "engine/functions.h"
#include "global.h"
#include "knife/comm/datalink.h"

// Functions in this file (original names from the debug build):
//   Datalink::verify(void const*, unsigned long) (0x020a6278), Datalink::crc(void const*, unsigned long) (0x020a6304)

extern "C" s32 Mem_Compare(const void *a, const void *b, u32 size); // compares size bytes, zero when equal
extern const u8 data_02124a80[]; // magic of a datalink block

// Datalink::verify(void const*, unsigned long) (0x020a6278): checks the magic, the version, the size, the item count and the CRC
BOOL Datalink::verify(const void *data, u32 size) {
    const u8 *block = (const u8 *)data;

    if (block == NULL) {
        return FALSE;
    }
    if (Mem_Compare(block, data_02124a80, 4) != 0) {
        return FALSE;
    }
    if (block[4] != 1) {
        return FALSE;
    }
    if (block[5] != 1) {
        return FALSE;
    }
    if (*(u32 *)(block + 8) != size) {
        return FALSE;
    }
    return *(u16 *)(block + 0xc) == crc(block + 0x10 + (*(u16 *)(block + 6) << 3), size - 0x10 - (*(u16 *)(block + 6) << 3));
}

// Datalink::crc(void const*, unsigned long) (0x020a6304): CRC-16 (reflected polynomial 0x8408), inverted at the end
u16 Datalink::crc(const void *data, u32 size) {
    const u8 *bytes = (const u8 *)data;
    u32 value = 0xffff;
    u32 i;
    s32 bit;

    for (i = 0; i < size; i++) {
        value ^= bytes[i];
        for (bit = 0; bit < 8; bit++) {
            if (value & 1) {
                value = (value >> 1) ^ 0x8408;
            } else {
                value = value >> 1;
            }
        }
    }
    return (u16)(value ^ 0xffff);
}

// Functions in this file (original names from the debug build):
//   DatalinkReader constructor and destructor (0x020a636c and 0x020a6384),
//   DatalinkReader::initialize(void const*, unsigned long) (0x020a6398), DatalinkReader::finalize() (0x020a63d8),
//   DatalinkReader::getDataBuffer(long) const (0x020a63f0), DatalinkReader::getDataSize(long) const (0x020a6438)

extern "C" void Engine_AssertFail(const char *file, const char *expr, const char *msg, s32 line); // assertion failure
extern const char data_02124a88[];
extern const char data_02124a94[];
extern const char data_02124a71[];
extern const char data_02124aa8[];
extern const char data_02124ab4[];
extern const char data_02124a65[];

// Emit the ROM's complete-object constructor and destructor entry points with their exact ABI symbols.
extern "C" {
DatalinkReader *_ZN14DatalinkReaderC1Ev(DatalinkReader *self) {
    self->block = NULL;
    self->table = NULL;
    self->blockSize = 0;
    self->initialized = 0;
    return self;
}

DatalinkReader *_ZN14DatalinkReaderD1Ev(DatalinkReader *self) {
    self->finalize();
    return self;
}
}

// DatalinkReader::initialize(void const*, unsigned long) (0x020a6398): finalizes, then takes the block if it verifies
BOOL DatalinkReader::initialize(const void *data, u32 size) {
    finalize();
    if (Datalink::verify(data, size) == 0) {
        return FALSE;
    }
    block = data;
    table = (u32 *)((u8 *)data + 0x10);
    blockSize = size;
    initialized = 1;
    return TRUE;
}

// DatalinkReader::finalize() (0x020a63d8): forgets the block
void DatalinkReader::finalize(void) {
    block = NULL;
    table = NULL;
    blockSize = 0;
    initialized = 0;
}

// DatalinkReader::getDataBuffer(long) const (0x020a63f0): the entry's data, at table + its offset
const void *DatalinkReader::getDataBuffer(s32 index) const {
    if (initialized == 0) {
        Engine_AssertFail(data_02124a88, data_02124a94, data_02124a71, 0x67);
    }
    return (u8 *)table + *(u32 *)((u8 *)table + index * 8);
}

// DatalinkReader::getDataSize(long) const (0x020a6438): the size of the entry
s32 DatalinkReader::getDataSize(s32 index) const {
    if (initialized == 0) {
        Engine_AssertFail(data_02124aa8, data_02124ab4, data_02124a65, 0x6f);
    }
    return *(s32 *)((u8 *)table + index * 8 + 4);
}
