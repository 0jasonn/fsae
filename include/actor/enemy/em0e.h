#ifndef ENEMY_EM0E_H
#define ENEMY_EM0E_H

#include "engine/entity.h"

typedef struct Vars_Em0e {
    /* 00 */ u8 unk_00[0x6c];
    /* 6c */ u8 unk_6c[2];
    /* 6e */ u16 pieceOffset;  // x offset of motiage1 from body0 (type2_piyori)
    /* 70 */ u8 unk_70;
    /* 71 */ u8 unk_71;
    /* 72 */ u8 unk_72[2];
    /* 74 */ u8 lastHealth;     // health seen at the last hit check
    /* 75 */ u8 partFlags;      // bit flags of the body parts
    /* 76 */ u16 timeout;
    /* 78 */ Entity *body0;     // the type 0 body this group is built around
    /* 7c */ Entity *motiage1;  // the type 1 part
} Vars_Em0e;

#endif
