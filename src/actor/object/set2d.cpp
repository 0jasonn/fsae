#include "engine/functions.h"
#include "global.h"
#include "actor/object/object_handlers.h"

// Set2d actor (module set2d), 0x0205a80c Set2d (original name): waits for its type bits, then clears the cell
// under it and spawns the set object.

typedef struct Vars_Set2d {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits; // ParseTypeBits(e->type), tested against em12_typeMasks[e->areaIndex]
} Vars_Set2d;

void Set2d(Entity *e) {
    Entity *child;
    switch (e->action) {
    case 0:
        e->action++;
        VARS(Vars_Set2d, e)->typeBits = ParseTypeBits(e->type);
        break;
    case 1:
        if (VARS(Vars_Set2d, e)->typeBits != (VARS(Vars_Set2d, e)->typeBits & em12_typeMasks[e->areaIndex])) {
            return;
        }
        KemuriSet(e);
        child = GetSetWork(0x21, e->type2, 0);
        if (child != NULL) {
            child->x.WORD = e->x.WORD;
            child->y.WORD = e->y.WORD;
            func_0208ae30(child);
        }
        RewCell((u16)(e->timer + 0x109), (e->x.HALF.HI >> 4) | ((e->y.HALF.HI >> 4) << 6), e->layer);
        AshimotoCheck(e);
        SoundReq(0x10);
        PutObjWork(e);
        break;
    }
}
