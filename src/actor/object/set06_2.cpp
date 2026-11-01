#include "engine/functions.h"
#include "global.h"
#include "actor/object/setmisc.h"
#include "actor/object/set06.h"

// Set06 actor, second unit (module set06). Address -> name:
//   0x02060bb0 set06_move, 0x02060ccc set06_die (original names)
//   0x02060dbc posAdd (original name)

extern UnkStruct_0212c648_S data_0212c648;
extern const EntityFunc data_02115a20[]; // indexed by e->action
extern const s16 data_02115a2c[];
extern const s16 data_02115a3c[];
extern u32 em12_typeMasks[]; // one mask per area

void posAdd(Entity *e, WWORK *offset);

// Cell index of the entity relative to the scroll position: row in bits 6+, column in the low bits
#define SET06_CELL(e)                                                                                   \
    ((u16)((((e)->x.HALF.HI - data_0212c648.scrollX) >> 4) | ((((e)->y.HALF.HI - data_0212c648.scrollY) >> 4) << 6)))

void set06_move(Entity *e) {
    u32 bits;

    if (--e->timer != 0) {
        return;
    }
    e->timer = 8;
    bits = VARS(Vars_Set06, e)->bits;
    if (bits == (bits & em12_typeMasks[e->areaIndex])) {
        if (e->unk_16 == e->subtimer) {
            return;
        }
        posAdd(e, &VARS(Vars_Set06, e)->posStep);
        RewCell(VARS(Vars_Set06, e)->cellId, SET06_CELL(e), e->layer);
        e->subtimer++;
        SoundReq(7);
        return;
    }
    if (e->subtimer == 0) {
        return;
    }
    RewCellBack(SET06_CELL(e), e->layer);
    posAdd(e, &VARS(Vars_Set06, e)->posBack);
    e->subtimer--;
    SoundReq(7);
}

void set06_die(Entity *e) {
    if (e->subAction == 0) {
        if (VARS(Vars_Set06, e)->bits == (VARS(Vars_Set06, e)->bits & em12_typeMasks[e->areaIndex])) {
            e->subAction++;
        }
        return;
    }
    if (--e->timer != 0) {
        return;
    }
    e->timer = 8;
    if (e->unk_16 != e->subtimer) {
        posAdd(e, &VARS(Vars_Set06, e)->posStep);
        RewCell(VARS(Vars_Set06, e)->cellId, SET06_CELL(e), e->layer);
        e->subtimer++;
        SoundReq(7);
        return;
    }
    if (VARS(Vars_Set06, e)->cellId != 0x159) {
        SoundReq(0x10);
    }
    PutObjWork(e);
}

void posAdd(Entity *e, WWORK *offset) {
    e->x.HALF.HI += offset->x;
    e->y.HALF.HI += offset->y;
}
