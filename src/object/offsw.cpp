#include "engine/functions.h"
#include "global.h"

// Offsw actor (module offsw). Address -> name:
//   0x02074c6c offsw_main (provisional name; dispatches on e->action)
//   0x02074c88 offsw_init (original name)
//   0x02074cac offsw_move (original name)

extern const EntityFunc offsw_actions[]; // offsw_actions, indexed by e->action
extern u32 em12_typeMasks[];             // indexed by e->areaIndex
extern const u32 flagBits[];             // indexed by e->type2

// File-local overlay. The word at 0x60 is a type bitmask, not a pointer.
typedef struct Vars_Offsw {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits; // ParseTypeBits(e->type), tested against em12_typeMasks[e->areaIndex]
} Vars_Offsw;

ARM void offsw_main(Entity *e) {
    offsw_actions[e->action](e);
}

ARM void offsw_init(Entity *e) {
    e->action++;
    VARS(Vars_Offsw, e)->typeBits = ParseTypeBits(e->type);
}

ARM void offsw_move(Entity *e) {
    Vars_Offsw *v;

    v = VARS(Vars_Offsw, e);
    if (v->typeBits != (v->typeBits & em12_typeMasks[e->areaIndex])) {
        return;
    }
    em12_typeMasks[e->areaIndex] = em12_typeMasks[e->areaIndex] & ~flagBits[e->type2];
    PutObjWork(e);
}
