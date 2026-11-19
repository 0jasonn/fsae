#ifndef WIP_SET1ST_H
#define WIP_SET1ST_H

#include "engine/functions.h"
#include "types.h"

extern const s16 trigTable[];
extern const s16 data_020d7f58[]; // trigTable + 0x100, the second half of the sine table

// Fields of the controller entity that set1st fills in.
typedef struct Vars_Set1stHead {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u8 setState; // 3 once the objects are made
    /* 7d */ u8 setFlag;
} Vars_Set1stHead;

// Fields of the orbiting part objects.
typedef struct Vars_Set1stPart {
    /* 00 */ u8 unk_00[0x7e];
    /* 7e */ u8 partIndex; // 1 for the second part, 2 for the third
} Vars_Set1stPart;

#endif
