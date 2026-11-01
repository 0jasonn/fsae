#include "engine/functions.h"
#include "global.h"
#include "game/bg_info.h"

// Object block (OBJInfo) of the cell animation loader: two buffers and their resource chunks
typedef struct ObjCellInfo {
    u8 unk_00[0x18];
    void *cellBuf1;   // 0x18
    void *cellChunk1; // 0x1c
    void *cellBuf2;   // 0x20
    void *cellChunk2; // 0x24
} ObjCellInfo;

extern "C" void initCellAnimation(ObjCellInfo *obj, s32 index1, s32 index2);

// initCellAnimation (0x020ac7dc): loads the cell data of two resources. index1 takes a 16-bit id, index2 a 31-bit id;
// the top bit of each selects the second resource table. -1 skips a resource.
void initCellAnimation(ObjCellInfo *obj, s32 index1, s32 index2) {
    if (index1 != -1) {
        u32 size;
        u8 kind;
        u32 id;

        kind = (u8)((u32)index1 >> 31);
        id = (u16)index1;
        size = getResourceSize(id, kind);
        obj->cellBuf1 = EL_GetGlobalAdr(size, 0x20);
        MI_CpuCopy8(getResourceData(id, kind), obj->cellBuf1, size);
        ResChunk_OpenKBEC(obj->cellBuf1, &obj->cellChunk1);
    }
    if (index2 == -1) {
        return;
    }
    {
        u32 size;
        u32 id;
        u8 kind;

        kind = (u8)((u32)index2 >> 31);
        id = (u32)index2 & 0x7fffffff;
        size = getResourceSize(id, kind);
        obj->cellBuf2 = EL_GetGlobalAdr(size, 0x20);
        MI_CpuCopy8(getResourceData(id, kind), obj->cellBuf2, size);
        Menu_ForwardC2cb4(obj->cellBuf2, &obj->cellChunk2);
    }
}
