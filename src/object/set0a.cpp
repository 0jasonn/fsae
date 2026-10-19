#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"

// Set actor unit 5 (module set). Address -> name (original names):
//   0x02057c64 Set0a

// File-local fields of the set actors (Entity bytes from 0x6c on).
typedef struct SetVars {
    /* 00 */ u8 unk_00[0x6c];
    /* 6c */ u16 retainFlag; // nonzero: the action table is skipped while encntSharedState is 0
    /* 6e */ u8 unk_6e[2];
    /* 70 */ u8 setKind;
    /* 71 */ u8 setParam1;
    /* 72 */ u8 setParam2;
} SetVars;

extern const EntityFunc data_020d8794[];
extern u8 encntSharedState;

ARM void Set0a(Entity *e) {
    if (VARS(SetVars, e)->retainFlag != 0 && encntSharedState == 0) {
        PutObjWork(e);
        return;
    }
    data_020d8794[e->action](e);
}
