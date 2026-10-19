#include "engine/functions.h"
#include "global.h"

// Set50 actor (module set50). Address -> name:
//   0x0207005c Set50 (original name)
//   0x02070098 set50_init, 0x020700dc set50_move (original names)
//   moji_init (0x02070140) is in scratch/agentD/nonmatching

typedef struct Vars_Set50 {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u8 spawnTotal; // spawns before the actor removes itself, set from set50_spawnTotalTable
    /* 7d */ u8 spawnBase; // spawn index base, set from set50_spawnBaseTable
} Vars_Set50;

extern const EntityFunc set50_actionsType0[]; // indexed by e->action, used when e->type == 0
extern const EntityFunc set50_actionsType1[]; // indexed by e->action, used for other types
extern const u8 set50_spawnBaseTable[]; // indexed by data_021348d8
extern const u16 set50_spawnTotalTable[]; // indexed by spawnBase
extern u8 data_021348d8;
extern const u8 *moji_posTables[]; // indexed by e->type - 1; each entry is indexed by e->type2

ARM void Set50(Entity *e) {
    if (e->type == 0) {
        set50_actionsType0[e->action](e);
    } else {
        set50_actionsType1[e->action](e);
    }
}

ARM void set50_init(Entity *e) {
    e->action = 1;
    e->timer = 0x3c;
    VARS(Vars_Set50, e)->spawnBase = set50_spawnBaseTable[data_021348d8];
    VARS(Vars_Set50, e)->spawnTotal = set50_spawnTotalTable[VARS(Vars_Set50, e)->spawnBase];
}

ARM void set50_move(Entity *e) {
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->timer = 0x10;
    GetSetWork(0x50, (u8)(VARS(Vars_Set50, e)->spawnBase + 1), e->subtimer);
    e->subtimer++;
    if (VARS(Vars_Set50, e)->spawnTotal > e->subtimer) {
        return;
    }
    PutObjWork(e);
}
