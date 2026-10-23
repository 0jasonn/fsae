#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"
#include "object/key_3.h"

// key module, units key_frame .. key_child_set (module key_3), 0x0206e054 .. 0x0206e210.
// Address -> name: 0x0206e054 key_frame, 0x0206e11c key_child, 0x0206e1b8 key_child_set, 0x0206e210 key_type_set

// Byte tables indexed by KnifeApp cursor index (cb0), each data_ name in the ROM
extern const u8 keyFrameBaseTable[];   // keyFrameBaseTable
extern const u8 keyTypeMaskTable[];    // keyTypeMaskTable
extern const u8 keyTypeShiftTable[];   // keyTypeShiftTable
extern const u8 keyTypeUnk21Table[];   // keyTypeUnk21Table
extern const u8 keyTypeBankTable[];    // keyTypeBankTable, indexed by bank value or cb0 + 4
extern u8 keyTypeFlags[];              // keyTypeFlags, rows of 8 indexed by type2

// Player count is the first byte of data_0212c7c8
typedef struct KeyPlayerState {
    u8 playerCount;
} KeyPlayerState;
extern KeyPlayerState data_0212c7c8;

ARM void key_frame(Entity *e) {
    u8 action = e->action;

    switch (action) {
    case 0:
        e->action = action + 1;
        e->unk_5e.b0 = 0;
        e->spriteSettings.b14 = 1;
        e->spriteSettings.b30 = 1;
        key_child_set(e);
        /* fall through */
    case 1:
        break;
    default:
        return;
    }
    e->unk_21 = data_0212c7c8.playerCount + keyFrameBaseTable[KNIFE_CURSOR_INDEX()] - 2;
    e->x.HALF.HI = e->parent->x.HALF.HI + 0x1c;
    e->y.HALF.HI = e->parent->y.HALF.HI - 8;
    if (KNIFE_CURSOR_INDEX() == 4 || KNIFE_CURSOR_INDEX() == 5) {
        e->y.HALF.HI = 0xff;
        e->x.HALF.HI = 0xff;
    }
}

ARM void key_child(Entity *e) {
    u8 action = e->action;

    switch (action) {
    case 0:
        e->action = action + 1;
        e->spriteSettings.b14 = 1;
        e->unk_5e.b0 = 1;
        e->spriteSettings.b30 = 1;
        /* fall through */
    case 1:
        break;
    default:
        return;
    }
    e->spriteSettings.b0 = e->parent->spriteSettings.b0;
    e->x.HALF.HI = e->parent->x.HALF.HI + 0xa + e->type2 * 0xb;
    e->y.HALF.HI = e->parent->y.HALF.HI + 0x10;
    key_type_set(e);
}

ARM void key_child_set(Entity *e) {
    u8 i;

    for (i = 0; i < data_0212c7c8.playerCount; i++) {
        Entity *child = GetSetWork(0x46, 0x15, i);
        if (child != NULL) {
            child->parent = e;
        }
    }
}
