#ifndef OBJECT_KEY_H
#define OBJECT_KEY_H

#include "engine/entity.h"

// Actor fields of the key family, file-local.
typedef struct Vars_Key {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u8 posIndex; // index into trigTable for the position on the key's circle
} Vars_Key;

#endif
