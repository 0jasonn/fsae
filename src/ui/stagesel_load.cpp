#include "engine/functions.h"
#include "sdk/mi/mi_uncompress.h"
#include "ui/stagesel.h"
#include "global.h"

// Request block of the stage select resource loader: resource id, VRAM destination and an unused word.
typedef struct SselLoadRequest {
    u32 resourceId;
    u32 dstAddr;
    u32 unused;
} SselLoadRequest;

// stagesel_loadsel (0x02078638): decompresses an LZ16 resource of the Zelda archive into the BG VRAM at 0x06000000 + mode.
void stagesel_loadsel(u16 index, int mode) {
    s32 size;
    SselLoadRequest request = {0, 0, 0};
    request.resourceId = (index & 0x80ffffff) | 0x0a000000;
    request.dstAddr = mode + 0x6000000;
    void *data = KnifeApp_getZeldaResource_08dde0(KnifeApp_getInstance(), &size, request.resourceId & 0xffffff);
    MI_UncompressLZ16(data, (void *)request.dstAddr);
}
