#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"
#include "engine/player.h"

// Actor em1d (original names from the debug build): Em1d, em1d_normal, em1d_damage. Dispatch tables are named in renames.txt.
typedef struct Vars_Em1d {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u16 grabTimer;     // 0x1e when the enemy grabs the player
    /* 72 */ u16 recoverTimer;  // 0x78 after a grab
} Vars_Em1d;

extern EntityFunc em1d_actions[];         // em1d_actions, indexed by func_02084a30(e)
extern EntityFunc em1d_normalActions[];   // em1d_normalActions, indexed by e->action

ARM void Em1d(Entity *e) {
    u8 actionIndex;

    func_02084700(e);
    actionIndex = func_02084a30(e);
    em1d_actions[actionIndex](e);
    func_0208ae30(e);
    e->spriteSettings.b30 = 1;
    e->spriteSettings.b14 = 1;
    if (actionIndex == 0 && e->action == 4) {
        e->unk_2e = 0;
    } else {
        e->unk_2e = 4;
    }
}

ARM void em1d_normal(Entity *e) {
    em1d_normalActions[e->action](e);
}

ARM void em1d_damage(Entity *e) {
    Vars_Em1d *vars = VARS(Vars_Em1d, e);
    Entity *hitter;
    PlayerData *player;
    u8 anim;

    if (e->contactFlags == 0x80) {
        hitter = e->contactedEntity;
        player = &data_0212ceb0[hitter->type];
        if (player->unk_26 == 0 && (player->statusFlags & 0xc80) == 0) {
            e->child = hitter;
            e->unk_5c = 0x1aa ^ (1 << (hitter->type * 2 + 1));
            e->action = 4;
            vars->grabTimer = 0x1e;
            vars->recoverTimer = 0x78;
            InitAnimationForceUpdate(e, 6);
        }
    } else {
        if (e->action == 4) {
            e->action = 1;
            e->unk_5c = 0x21ff;
            e->layer |= 0xc000;
            func_0208ae78(e);
        }
        e->unk_42 = 0x18;
        anim = ((e->direction >> 4) + 4) & 0xff;
        InitAnimationForceUpdate(e, anim);
    }
    GenericKnockback(e, em1d_actions);
}
