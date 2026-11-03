#include "engine/functions.h"
#include "global.h"
#include "actor/object/setcommon.h"
#include "actor/object/g_callees.h"
#include "actor/object/set13.h"

// Set13 actor, hidari (left) wall cell writer (module set13). Address -> name:
//   0x02064770 hidari_writecell (original name writecell(OBJ_WORK_*))

extern const s16 cellDeltaTable[];        // cellDeltaTable, cell offset per animation state (indexed by state/2)
extern const u16 set13_cellValueTable[];  // cell value per animation state (indexed by state/2)

void hidari_writecell(Entity *e) {
    u32 offset;
    s32 dx;
    u16 value;
    u16 *cell;
    u16 *p;
    offset = e->animationState & ~1;
    value = *(const u16 *)((const u8 *)set13_cellValueTable + offset);
    dx = (s8)*(const s16 *)((const u8 *)cellDeltaTable + offset);
    cell = VARS(Vars_Set13, e)->cellPtr;
    p = cell + dx;
    VARS(Vars_Set13, e)->cellValue70 = *p;
    *p = value;
    p = p - dx;
    *p = value;
    p = p - dx;
    VARS(Vars_Set13, e)->cellValue74 = *p;
    *p = value;
}
