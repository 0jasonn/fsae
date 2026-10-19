#include "engine/functions.h"
#include "global.h"
#include "object/setmisc.h"

// Set06 actor (module set06). Address -> name:
//   0x02060a9c Set06 (original name)

typedef struct WWORK {
    s16 x; // offset added to the entity's x (integer half)
    s16 y; // offset added to the entity's y (integer half)
} WWORK;

typedef struct Vars_Set06 {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 bits; // one bit per type group covered by this set (set06_init)
    /* 64 */ WWORK posStep; // offset applied when the set moves forward
    /* 68 */ WWORK posBack; // offset applied when the set moves back
    /* 6c */ u16 cellId; // id passed to RewCell
} Vars_Set06;

typedef struct UnkStruct_0212c648_S {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 scrollX;
    /* 1a */ u16 scrollY;
} UnkStruct_0212c648_S;

extern UnkStruct_0212c648_S data_0212c648;
extern const EntityFunc data_02115a20[]; // indexed by e->action
extern const s16 data_02115a2c[];
extern const s16 data_02115a3c[];
extern u32 em12_typeMasks[]; // one mask per area

void posAdd(Entity *e, WWORK *offset);

// Cell index of the entity relative to the scroll position: row in bits 6+, column in the low bits
#define SET06_CELL(e)                                                                                   \
    ((u16)((((e)->x.HALF.HI - data_0212c648.scrollX) >> 4) | ((((e)->y.HALF.HI - data_0212c648.scrollY) >> 4) << 6)))

ARM void Set06(Entity *e) {
    data_02115a20[e->action](e);
}
