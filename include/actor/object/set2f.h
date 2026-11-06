#ifndef OBJECT_SET2F_H
#define OBJECT_SET2F_H

#include "engine/entity.h"

// mapState as read by rewlever: grid origin of the map cells.
typedef struct Set2fGridOrigin {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 originX;
    /* 1a */ u16 originY;
} Set2fGridOrigin;

typedef struct Vars_Set2f {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u8 triggered; // set once set2f_move has flipped the actor
} Vars_Set2f;

#endif
