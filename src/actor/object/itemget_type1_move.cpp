#include "engine/functions.h"
#include "global.h"
#include "actor/object/setcommon.h"
#include "actor/object/set26.h"
#include "actor/object/itemget_actions.h"

// Item unit of the set26 module (module itemget). Address -> name:
//   0x02067a60 itemget_type1_move (original name)

// Once the area flags hold all type bits of the item, rewrites the 2x2 cells under it and removes it.
void itemget_type1_move(Entity *e) {
    s32 cell;

    if (VARS(Vars_Set26, e)->typeBits != (VARS(Vars_Set26, e)->typeBits & em12_typeMasks[e->areaIndex])) {
        return;
    }
    cell = (u16)(((e->x.HALF.HI - 8 - mapState.originX) >> 4) | (((e->y.HALF.HI - 8 - mapState.originY) >> 4) << 6));
    RewCell(0x14e, cell, e->layer);
    RewCell(0x14f, cell + 1, e->layer);
    RewCell(0x150, cell + 0x40, e->layer);
    RewCell(0x151, cell + 0x41, e->layer);
    func_02085f98(e, 0x17);
    PutObjWork(e);
}
