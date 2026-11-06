#include "engine/functions.h"
#include "global.h"
#include "actor/object/setmisc.h"
#include "actor/object/set06.h"

// Set06 actor (module set06). Address -> name:
//   0x02060a9c Set06 (original name)

extern UnkStruct_0212c648_S mapState;
extern const EntityFunc data_02115a20[]; // indexed by e->action
extern const s16 data_02115a2c[];
extern const s16 data_02115a3c[];
extern u32 em12_typeMasks[]; // one mask per area

void posAdd(Entity *e, WWORK *offset);

// Cell index of the entity relative to the scroll position: row in bits 6+, column in the low bits
#define SET06_CELL(e)                                                                                   \
    ((u16)((((e)->x.HALF.HI - mapState.scrollX) >> 4) | ((((e)->y.HALF.HI - mapState.scrollY) >> 4) << 6)))

void Set06(Entity *e) {
    data_02115a20[e->action](e);
}
