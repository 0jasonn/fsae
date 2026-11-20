#include "engine/functions.h"
#include "actor/enemy/em1d_possess.h"

// em1d_possess (0x0202fe98): the enemy hangs on its player. While the player mashes keys the grab timer counts down and
// every 0x78 frames a heart is drained; when the grab ends (or the player becomes busy) the enemy is thrown off in a
// random quarter-turn direction.
void em1d_possess(Entity *e) {
    Vars_Em1dPossess *vars = VARS(Vars_Em1dPossess, e);
    s32 slot;
    s32 released;

    UpdateAnimationSingleFrame(e);
    ObjPosCopyOfs32(e->child, e, 0, (s32)(s8)((e->frame & 3) - 1) << 16);
    e->z.HALF.HI -= 4;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        if (e->child != playerWork[*Knife_Single_SinglePlay_GetInstance()].entity) {
            vars->grabTimer = 0;
        }
    }
    slot = e->child->type * 0x94;
    if (data_0212ceec[slot] != 0) {
        func_02084a20(e);
        return;
    }
    if ((*(u16 *)&data_0212cee6[slot] & 1) != 0) {
        return;
    }
    if (playerKeys[e->child->type] != 0) {
        vars->grabTimer -= 1;
    }
    released = 0;
    if (e->child->action == 3 || e->child->action == 2 || data_0212ced6[e->child->type * 0x94] != 0 ||
        (*(u16 *)&data_0212cee6[e->child->type * 0x94] & 0xc80) != 0) {
        vars->grabTimer = 0;
        released = 1;
    }
    if (vars->grabTimer != 0) {
        vars->recoverTimer -= 1;
        if (vars->recoverTimer != 0) {
            return;
        }
        vars->recoverTimer = 0x78;
        AddHeart(e->child, -4);
        e->child->iframes = 0x10;
        e->child->contactFlags = 0xa4;
        return;
    }
    e->action = 3;
    e->subtimer = 0x2d;
    e->speed = 0x60;
    e->unk_5c = 0x21ff;
    e->layer |= 0xc000;
    func_0208ae78(e);
    e->baseDirection = (Random() & 0x1f) ^ 0x10;
    e->direction = e->baseDirection;
    e->animationState = e->direction >> 4;
    if (released != 0) {
        InitAnimationForceUpdate(e, e->animationState);
        return;
    }
    e->iframes = 0xf4;
    e->unk_42 = 0x10;
    InitAnimationForceUpdate(e, (e->direction >> 4) + 4);
}
