#include "engine/functions.h"
#include "global.h"
#include "game/subtask.h"

// Subtask buffer release, 0x0209d690 to 0x0209d78c: frees the slot and object info blocks.

extern u32 data_0217a2b8[];

// subTask_free_slot (0x0209d690): frees the two pointer slots of entry index (each slot is a pointer and a size word)
ARM void subTask_free_slot(s32 index) {
    u32 *slot = data_0217a2b8 + index * 8;

    if (slot[0] != 0) {
        func_0208e188((void *)slot[0]);
        slot[0] = 0;
        slot[1] = 0;
    }
    if (slot[2] != 0) {
        func_0208e188((void *)slot[2]);
        slot[2] = 0;
        slot[3] = 0;
    }
    if (slot[4] != 0) {
        func_0208e188((void *)slot[4]);
        slot[4] = 0;
        slot[5] = 0;
    }
    if (slot[6] != 0) {
        func_0208e188((void *)slot[6]);
        slot[6] = 0;
        slot[7] = 0;
    }
}

// subTask_free_objinfo (0x0209d714)
ARM void subTask_free_objinfo(OBJInfo *info) {
    if (info->block00 != 0) {
        func_0208e188(info->block00);
        info->block00 = 0;
    }
    if (info->block08 != 0) {
        func_0208e188(info->block08);
        info->block08 = 0;
    }
    if (info->block10 != 0) {
        func_0208e188(info->block10);
        info->block10 = 0;
    }
    if (info->block18 != 0) {
        func_0208e188(info->block18);
        info->block18 = 0;
        info->unk_1c = 0;
    }
    if (info->block20 != 0) {
        func_0208e188(info->block20);
        info->block20 = 0;
    }
}
