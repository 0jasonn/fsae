#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/g_callees.h"

// Set16 actor, second unit (module set16). Address -> name:
//   0x02064e18 set16_move (original name)

typedef struct Vars_Set16_2 {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 requestBits; // request bits from the parent; cleared when the actor acts
} Vars_Set16_2;

extern u32 em12_typeMasks[];
extern const EntityFunc set16_subActionTable[]; // indexed by e->subAction (was set16_subActionTable)

ARM void set16_move(Entity *e) {
    u32 request;
    u8 *player;

    if (e->type < 9) {
        func_02084228(e);
    } else {
        func_02084200(e);
        request = VARS(Vars_Set16_2, e)->requestBits;
        player = Knife_Single_SinglePlay_GetInstance();
        player[0xd] = player[0xd] | (u8)request;
    }
    set16_subActionTable[e->subAction](e);
    VARS(Vars_Set16_2, e)->requestBits = 0;
}
