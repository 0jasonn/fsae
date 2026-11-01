#ifndef OBJECT_NAMEPLATE_H
#define OBJECT_NAMEPLATE_H

#include "engine/entity.h"

typedef struct Vars_NamePlate {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u8 unk_64[3];
    /* 67 */ u8 hideMask; // set to 0xff on init
} Vars_NamePlate;

#endif
