#include "engine/functions.h"
#include "engine/blzload.h"

// LoadBlzFile(path, heap, align, outSize) (0x020b7b1c, was LoadBlzFile): loads a BLZ-compressed file from the archive into a
// block of the heap and decompresses it in place. The size after decompression is the file size plus the extra size stored in
// the last 4 bytes of the file. align (4 means none) is added to the block size and the data starts at the aligned address.
// Returns the block (NULL on failure) and stores the decompressed size in *outSize when outSize is not NULL
void *LoadBlzFile(const char *path, void *heap, s32 align, u32 *outSize) {
    u32 trailer;
    BlzFile file;
    u32 fileSize;
    u32 totalSize;
    u8 *mem;
    s32 pad;
    s32 result;
    u8 *aligned;

    FS_InitFile(&file);
    if (!FS_FindDir(&file, (void *)path)) {
        return NULL;
    }
    fileSize = Fs_GetFileLengthWrap(&file);
    mem = NULL;
    if (FS_SeekFile(&file, -4, 2) && FS_ReadFile(&file, &trailer, 4) == 4) {
        totalSize = trailer + fileSize;
        if (FS_SeekFile(&file, 0, 0)) {
            pad = 0;
            if (align != 4) {
                pad = align;
            }
            mem = (u8 *)func_020c2c34(heap, totalSize + pad);
            if (mem != NULL) {
                aligned = (u8 *)(((u32)mem + (align - 1)) & ~(align - 1));
                s32 n;
                result = -1;
                n = FS_ReadFile(&file, aligned, fileSize);
                if (n == fileSize) {
                    result = MI_SecureUncompressBLZ(aligned, fileSize, totalSize);
                    if (result >= 0) {
                        if (outSize != NULL) {
                            *outSize = totalSize;
                        }
                    }
                }
                if (result < 0) {
                    Heap_VirtualFree(heap, mem);
                    mem = NULL;
                }
            }
        }
    }
    FS_CloseFile(&file);
    return mem;
}
