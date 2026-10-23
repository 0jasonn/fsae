#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/setcommon_g.h"
#include "object/set19.h"

// Set19 actor (module set19). Address -> name:
//   0x02065834 Set19 (dispatcher, was Set19)
//   0x02065850 set19_init, 0x020658b4 set19_move, 0x020658dc set19_wait

// Dispatcher: runs the handler for the current action.
ARM void Set19(Entity *e) {
    set19_stateTable[e->action](e);
}

// Init: advances the action, stores the BG cell pointer and its value under the entity.
ARM void set19_init(Entity *e) {
    int bg;
    int cell;

    e->action++;
    bg = GetBgBuffAdrs(e->layer);
    cell = ((e->x.HALF.HI - data_0212c648.unk_18) >> 4) | (((e->y.HALF.HI - data_0212c648.unk_1a) >> 4) << 6);
    VARS(Vars_Set19, e)->cellPtr = (u16 *)(bg + 4 + cell * 2);
    VARS(Vars_Set19, e)->cellValue = *VARS(Vars_Set19, e)->cellPtr;
}

// Waits until the BG cell changes from the value taken in set19_init, then sets the timer to 15 and advances.
ARM void set19_move(Entity *e) {
    u8 action;

    if (VARS(Vars_Set19, e)->cellValue != *VARS(Vars_Set19, e)->cellPtr) {
        action = e->action;
        e->timer = 0xf;
        e->action = action + 1;
    }
}

// Counts the timer down. At 0 it sets the area mask bits of the type, fires the area's MultiEventSet when type2 is
// set, and removes the entity.
ARM void set19_wait(Entity *e) {
    u8 area;

    if (--e->timer != 0) {
        return;
    }
    area = e->areaIndex;
    em12_typeMasks[area] |= flagBits[e->type];
    if (e->type2 != 0) {
        MultiEventSet((u16 *)GetInfoAdrs(area, e->type2), (u8)data_0213492c[area * 2], (u8)em12_spawnOffsetY[area * 2], area);
    }
    PutObjWork(e);
}
