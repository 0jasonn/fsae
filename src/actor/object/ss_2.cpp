#include "engine/functions.h"
#include "global.h"
#include "actor/object/pot.h"

// Shutter actor (module ss). Address -> name:
//   0x02067bdc shutter_set (original name, state table data_02115b1c indexed by e->action)
//   (ss_init at 0x02067bf8 is parked in scratch/agentC/nonmatching)

extern EntityFunc data_02115b1c[]; // state table indexed by e->action

void shutter_set(Entity *e) {
    data_02115b1c[e->action](e);
}

// Shutter actor (module ss): ss_init 0x02067bf8, ss_check 0x02067c4c, ss_wait 0x02067cc0.
// The cell index is written x term first; mwcc then puts the shifted y term on the left in the output.

// Shutter fields past the shared header
typedef struct Vars_Shutter {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 linkWord; // type of the linked actor, low byte is passed to GetInfoAdrs
} Vars_Shutter;

#define SHUTTER_CELL(e) \
    ((u16)(((((e)->x.HALF.HI - mapState.scrollX) >> 4) | ((((e)->y.HALF.HI - mapState.scrollY) >> 4) << 6))))

void ss_init(Entity *e) {
    e->action = 1;
    e->subtimer = func_02083d4c(SHUTTER_CELL(e), e->layer);
}

void ss_check(Entity *e) {
    Vars_Shutter *v = VARS(Vars_Shutter, e);
    int state = func_02083d4c(SHUTTER_CELL(e), e->layer);
    u32 link;

    if (e->subtimer == state) {
        return;
    }
    link = state == 0xf ? e->type2 : e->timer;
    e->action = 2;
    e->unk_16 = 0;
    v->linkWord = link;
}

void ss_wait(Entity *e) {
    Vars_Shutter *v = VARS(Vars_Shutter, e);
    u8 area;

    e->unk_16 = e->unk_16 - 1;
    if (e->unk_16 != 0) {
        return;
    }
    e->action = 1;
    e->subtimer = func_02083d4c(SHUTTER_CELL(e), e->layer);
    area = e->areaIndex;
    MultiEventSet((u16 *)GetInfoAdrs(area, (u8)v->linkWord), (u8)data_0213492c[area * 2],
                  (u8)em12_spawnOffsetY[area * 2], area);
}
