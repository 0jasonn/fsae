#include "engine/functions.h"
#include "global.h"

// Functions in this file (original names from the debug build):
//   Knife::Message::KnifeInfoGetter::getVariable(int) const (0x020a1668)

// Source of the variables a message can show (Knife::Message::KnifeInfoGetter). Only the fields used here are named.
typedef struct KnifeInfoGetter {
    u8 unk_00[0x04];
    s32 *info;          // 0x04: four variables at +0x14 to +0x20, NULL when there is no info block
    s32 fallback;       // 0x08: value used while info is NULL
} KnifeInfoGetter;

// KnifeInfoGetter::getVariable(int) const (0x020a1668): the variable index (0 to 3) of the info block, or 0 for other
// indexes; the fallback value while there is no info block
extern "C" s32 Knife_Message_KnifeInfoGetter_getVariable(const void *a, s32 index);
ARM s32 Knife_Message_KnifeInfoGetter_getVariable(const void *a, s32 index) {
    const KnifeInfoGetter *self = (const KnifeInfoGetter *)a;
    s32 value = 0;

    if (self->info != NULL) {
        switch (index) {
        case 0:
            value = self->info[5];
            break;
        case 1:
            value = self->info[6];
            break;
        case 2:
            value = self->info[7];
            break;
        case 3:
            value = self->info[8];
            break;
        }
    } else {
        value = self->fallback;
    }
    return value;
}
