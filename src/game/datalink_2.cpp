#include "engine/functions.h"
#include "global.h"
#include "game/datalink.h"

// Functions in this file (original names from the debug build):
//   DatalinkReader::initialize(void const*, unsigned long) (0x020a6398), DatalinkReader::finalize() (0x020a63d8),
//   DatalinkReader::getDataBuffer(long) const (0x020a63f0), DatalinkReader::getDataSize(long) const (0x020a6438)

extern "C" void Engine_AssertFail(const char *file, const char *expr, const char *msg, s32 line); // assertion failure
extern const char data_02124a88[];
extern const char data_02124a94[];
extern const char data_02124a71[];
extern const char data_02124aa8[];
extern const char data_02124ab4[];
extern const char data_02124a65[];

// DatalinkReader::initialize(void const*, unsigned long) (0x020a6398): finalizes, then takes the block if it verifies
ARM BOOL DatalinkReader::initialize(const void *data, u32 size) {
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
ARM void DatalinkReader::finalize(void) {
    block = NULL;
    table = NULL;
    blockSize = 0;
    initialized = 0;
}

// DatalinkReader::getDataBuffer(long) const (0x020a63f0): the entry's data, at table + its offset
ARM const void *DatalinkReader::getDataBuffer(s32 index) const {
    if (initialized == 0) {
        Engine_AssertFail(data_02124a88, data_02124a94, data_02124a71, 0x67);
    }
    return (u8 *)table + *(u32 *)((u8 *)table + index * 8);
}

// DatalinkReader::getDataSize(long) const (0x020a6438): the size of the entry
ARM s32 DatalinkReader::getDataSize(s32 index) const {
    if (initialized == 0) {
        Engine_AssertFail(data_02124aa8, data_02124ab4, data_02124a65, 0x6f);
    }
    return *(s32 *)((u8 *)table + index * 8 + 4);
}
