#include "engine/functions.h"
#include "global.h"

// Small wrappers at the end of the range, 0x02082fbc to 0x02082ffc. Each one passes its arguments on, most of them
// as a tail call. The class method WirelessAllocator::deallocate is kept under its plain symbol name.
//   WirelessAllocator_deallocate (0x02082fbc): frees a block unless it is NULL.
//   ElGlobalAdrThunk (0x02082fd4): returns EL_GetGlobalAdr(offset, size).
//   CallbackForJpeg (0x02082fe8): decompresses the JPEG block with MI_UncompressLZ16 (arguments swapped).

extern "C" void MI_UncompressLZ16(const void *src, void *dst);

// WirelessAllocator_deallocate (0x02082fbc)
ARM void WirelessAllocator_deallocate(void *allocator, void *block) {
    if (block != NULL) {
        func_0208e188(block);
    }
}

// ElGlobalAdrThunk (0x02082fd4)
ARM void *ElGlobalAdrThunk(void *unused, u32 offset, u32 size) {
    return ((void *(*)(u32, u32))EL_GetGlobalAdr)(offset, size);
}

// CallbackForJpeg (0x02082fe8)
ARM void CallbackForJpeg(void *a, void *b) {
    ((void (*)(const void *, void *))MI_UncompressLZ16)(b, a);
}
