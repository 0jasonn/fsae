#include "engine/functions.h"
#include "global.h"
#include "actor/object/effectdecls.h"
#include "actor/object/cellcalls.h"

// Set49 family (module set49), 0x0206f680 .. 0x0206f69c (dispatcher).
// Address -> name: 0x0206f680 Set49

// Action table of Set49, set49Table
extern const EntityFunc set49Table[];

void Set49(Entity *e) {
    set49Table[e->action](e);
}

extern "C" void searchCell(Entity *e);
extern u16 searchTargetTable[];

// Set49 family, second unit (module set49), 0x0206f69c: set49_init (original name).

typedef struct Vars_Set49 {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u16 cellIndex; // map cell computed from the position
} Vars_Set49;

// set49_init, 0x0206f69c: starts the action, computes the map cell and looks it up in searchTargetTable
void set49_init(Entity *e) {
    u16 *p;
    u16 v;
    s32 key;
    u32 idx;

    e->action = 1;
    VARS(Vars_Set49, e)->cellIndex = ((e->x.HALF.HI - mapState.originX) >> 4) |
                                     (((e->y.HALF.HI - mapState.originY) >> 4) << 6);
    key = GetCellKind(VARS(Vars_Set49, e)->cellIndex, e->layer);
    p = searchTargetTable;
    v = 0x3c6;
    for (;;) {
        if (key == v) {
            idx = ((u32)p - (u32)searchTargetTable) >> 1;
            e->type = idx;
            if (e->type >= 8) {
                SoundReq(0x10);
            }
            searchCell(e);
            return;
        }
        p++;
        v = *p;
        if (v == 0xffff) {
            PutObjWork(e);
            return;
        }
    }
}
