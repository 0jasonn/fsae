#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Info block with the kind in its low five bits.
typedef struct InfoBlock {
    u8 kind;
} InfoBlock;

// Object whose info pointer sits at +8.
typedef struct InfoHolder {
    u8 unk_00[8];
    InfoBlock *info;
} InfoHolder;

extern "C" u8 Info_GetKind5(InfoHolder *self);

// Info_GetKind5(self) (0x0200b43c): the low five bits of the kind of the info block, 0 when there is none.
ARM u8 Info_GetKind5(InfoHolder *self) {
    InfoBlock *info;

    info = self->info;
    return info != NULL ? (info->kind & 0x1f) : 0;
}
