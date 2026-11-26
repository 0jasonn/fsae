#ifndef ENGINE_BLZLOAD_H
#define ENGINE_BLZLOAD_H

#include "types.h"
#include "sdk/fs/fs_file.h"
#include "sdk/fs/fs_wrap_api.h"

extern "C" {
s32 MI_SecureUncompressBLZ(void *data, u32 compressedSize, u32 uncompressedSize);
void *func_020c2c34(void *heap, s32 size);

}

#endif
