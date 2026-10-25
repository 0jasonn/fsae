#ifndef WIP_F_RECT_OBJ_F_H
#define WIP_F_RECT_OBJ_F_H

// RectObj record of rect_obj.cpp, with the field at +0x14 used by the RectObjLink classes (vtable data_02126d48, data_02126d84)

#include "types.h"

// The flag byte as bits: bit 0 freezes the bounds
typedef struct RectFlagBits {
    u8 frozen : 1;     // bit 0
    u8 unk_bit1 : 1;   // bit 1
    u8 hit : 1;        // bit 2: result of RectObj_hitTest, see RectObj_updateHitFlag
    u8 rest : 5;
} RectFlagBits;

typedef struct RectObjF {
    void *vtable;      // 0x00
    s16 offsetX;       // 0x04
    s16 offsetY;       // 0x06
    s16 sizeX;         // 0x08
    s16 sizeY;         // 0x0a
    s16 boundX;        // 0x0c
    s16 boundY;        // 0x0e
    u8 flags;          // 0x10: bit 0 freezes the bounds, bit 2 is the hit flag (RectObj_updateHitFlag)
    u8 unk_11[3];
    s32 unk_14;        // 0x14
    u16 unk_18;        // 0x18: RectObjLink2 only
} RectObjF;

#endif
