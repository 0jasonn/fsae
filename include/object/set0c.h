#ifndef UNKNOWN_WIP_F_SET0C_H
#define UNKNOWN_WIP_F_SET0C_H

#include "object/setcommon.h"

// Set0c actor fields (file-local overlay for src/object/set0c*.cpp, not shared).
typedef struct Vars_Set0c {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits;      // ParseTypeBits(e->type), tested against em12_typeMasks[e->areaIndex]
    /* 64 */ u8 unk_64[0x18];
    /* 7c */ u16 cell;          // grid cell index computed in set0c_init, passed to RewCell / RewCellBack
    /* 7e */ u16 vanishDelay;   // frames left before the cell is released
} Vars_Set0c;
#define VS0C(e) VARS(Vars_Set0c, e)

extern const EntityFunc set0c_typeActions[];   // set0c_typeActions, indexed by e->type

#endif
