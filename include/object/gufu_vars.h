#ifndef WIP_D_GUFU_VARS_H
#define WIP_D_GUFU_VARS_H

// Gufu body fields past the shared part of Entity (file-local overlay used by the gufu units).
#include "engine/entity.h"

typedef struct Vars_GufuBody {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u8 angle;   // index into trigTable (sine), the cosine is 0x40 entries later
    /* 61 */ u8 radiusX; // scale of the x offset
    /* 62 */ u8 radiusY; // scale of the y offset
} Vars_GufuBody;

#endif
