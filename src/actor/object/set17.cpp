#include "engine/functions.h"
#include "global.h"
#include "actor/object/setcommon.h"
#include "actor/object/g_callees.h"

// Set17 actor (module set17). Address -> name:
//   0x020654c0 set17_run (dispatcher, was set17_run)

extern const EntityFunc set17_stateTable[]; // indexed by e->action (was set17_stateTable)
extern const u8 set17_hitbox[];             // was set17_hitbox

void set17_run(Entity *e) {
    set17_stateTable[e->action](e);
}

// Set17 actor (module set17). Address -> name:
//   0x020654dc set17_init (original name)

extern const u8 set17_hitbox[]; // 0x02115abc

void set17_init(Entity *e) {
    u32 spriteWord;
    u8 nextAction;
    spriteWord = *(u32 *)&e->spriteSettings;
    spriteWord = (spriteWord & ~0x3) | 1;
    *(u32 *)&e->spriteSettings = spriteWord;
    e->unk_2e = 0;
    nextAction = e->action + 1;
    e->action = nextAction;
    e->statusFlags = 0x8c;
    e->unk_40 = 0x36;
    e->hitbox = set17_hitbox;
    e->unk_5c = 0x200;
    func_02084180(e);
    InitAnimationForceUpdate(e, 7);
    SoundReq(0x1d);
}

// Set17 actor (module set17). Address -> name:
//   0x02065548 set17_move (original name)

void set17_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame == 0) {
        return;
    }
    if (e->frame & 0x80) {
        func_020841b0(e);
        PutObjWork(e);
        return;
    }
    TaimatuIgnition(e, 5);
}
