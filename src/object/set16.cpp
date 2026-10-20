#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/g_callees.h"

// Set16 actor (module set16). Address -> name:
//   0x02064bf4 Set16 (original name)

extern const EntityFunc set16_stateTable[]; // indexed by e->action (was set16_stateTable)
extern u8 frameCounter[];                // was frameCounter, read as u16 (bit 1 selects the sprite flag)

typedef struct Vars_Set16 {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ s32 counter; // frames left before the actor is removed
} Vars_Set16;

ARM void Set16(Entity *e) {
    if (VARS(Vars_Set16, e)->counter != 0) {
        VARS(Vars_Set16, e)->counter = VARS(Vars_Set16, e)->counter - 1;
        if (VARS(Vars_Set16, e)->counter == 0) {
            PutObjWork(e);
            return;
        }
        if ((u32)VARS(Vars_Set16, e)->counter < 0x10) {
            e->spriteSettings.b0 = (*(u16 *)frameCounter & 0x2) >> 1;
        }
    }
    set16_stateTable[e->action](e);
}
