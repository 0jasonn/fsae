#include "engine/functions.h"
#include "actor/object/set5c_2.h"
#include "actor/object/pot.h"

// 0x0205fadc (original name). Removes the actor from its cell once its area mask says the cell is clear, then
// releases the work slot.
typedef struct Vars_Set5c {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u32 maskSource; // compared against the per-area mask before the actor may vanish
    /* 68 */ u32 savedCell; // BG cell value to write back
} Vars_Set5c;

void set5c_vanish(Entity *e) {
    u32 value = VARS(Vars_Set5c, e)->maskSource;
    u32 mask;

    mask = em12_typeMasks[e->areaIndex];
    if (value != (value & mask)) {
        return;
    }
    if (((int (*)(Entity *))func_0208583c)(e) != 0) {
        KemuriSet(e);
    }
    RewCellBack((u16)VARS(Vars_Set5c, e)->savedCell, e->layer);
    PutObjWork(e);
}
