#include "engine/functions.h"
#include "global.h"
#include "object/c_decls.h"

// Set5b actor (module set5b). Address -> name:
//   0x0205f928 Set5b (name from symbols.txt)
//   (set5c_init at 0x0205f9d4 is in the next unit)

// Actor fields past the shared header: the type bit mask read at init
typedef struct Vars_Set5b {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeMask;
} Vars_Set5b;

extern u16 data_0213492c[]; // per-area offset, read at [area * 2]
extern u16 em12_spawnOffsetY[]; // per-area offset, read at [area * 2]
extern u32 em12_typeMasks[]; // one mask per area

ARM void Set5b(Entity *e) {
    Vars_Set5b *v = VARS(Vars_Set5b, e);
    u8 area;

    if (e->action == 0) {
        e->action = 1;
        v->typeMask = ParseTypeBits(e->type);
        return;
    }
    area = e->areaIndex;
    if (v->typeMask != (v->typeMask & em12_typeMasks[area])) {
        return;
    }
    MultiEventSet((u16 *)GetInfoAdrs(area, e->type2), (u8)data_0213492c[area * 2],
                  (u8)em12_spawnOffsetY[area * 2], area);
    PutObjWork(e);
}
