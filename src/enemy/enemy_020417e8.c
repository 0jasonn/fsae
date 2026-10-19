// Implementer B, round 3: functions of 0x020417e8 to 0x02048264 (matched, all 0 differ, 0 size mismatches).
// Address -> name (also in scratch/agentB/renames.txt):
//   Em29 Em29    em29_init em29_init
//   em29_move em29_move          em29_vacuumInit em29_vacuumInit
//   em29_vacuum em29_vacuum        em29_vacuumEnd em29_vacuumEnd
//   em29_die em29_die       breakSekichu breakSekichu
//   movecheck movecheck               hikiyoseSet hikiyoseSet
//   em30_type0_init em30_type0_init               em30_type0_wait em30_type0_wait
//   type0_attackBlossom type0_attackBlossom           em30_type1 em30_type1
//   em30_type2 em30_type2         setUde setUde
//   setFlower setFlower       Enemy_SetSpriteFromTable Enemy_SetSpriteFromTable
//   flowerTamaSet flowerTamaSet           Em30CheckAttack Em30CheckAttack
//   Em30GetRightColor Em30GetRightColor           Enemy_RunHandlerTable Enemy_RunHandlerTable
//   em31_normal em31_normal             em31_damage em31_damage
//   em31_move em31_move          Enemy_StartScript Enemy_StartScript
//   Enemy_ArmSharedState Enemy_ArmSharedState             Encounter Encounter
//   plback plback                plfront plfront
// Not matched (kept in scratch/agentB/nonmatching): plhikiyose, type0_kamae, em30_type3, damageCheck,
// em31_init, honyaMove, honyaGetInfo, func_0204363c.

#include "enemy/enemy_020417e8.h"
#include "global.h"

extern const EntityFunc data_020d34a4[];
extern const u16 data_020d3486[];
extern const s8 data_020d346c[];
extern const s8 data_020d346f[];
extern const u16 data_020d347a[];
extern u8 data_021348ec[];
extern const u8 data_020d35e0[];
extern const u8 data_020d35fc[];
extern const EntityFunc data_020d35e4[];
extern const EntityFunc data_020d360c[];
extern const u8 data_020d34e2[];

// Em29 (0x020417e8): a follower whose parent raises trigger bit 0 restarts in action 6.
// Then runs the action handler and, for type 2, the two helpers below and a 0x1e-frame cycle that plays sound 0x59.
ARM void Em29(Entity *e) {
    if (e->type2 != 0) {
        Vars_Parent *parent = VARS(Vars_Parent, e->parent);
        if (parent->triggerFlags & 1) {
            e->action = 6;
            e->timer = 0x1e;
            SPRITE_VIEW(e)->b8 |= 2;
            W(e)->subPosX = 0xf0;
            W(e)->subPosY = 0x120;
            parent->triggerFlags &= 0xfe;
        }
    }
    data_020d34a4[e->action](e);
    if (e->type != 2) {
        return;
    }
    plhikiyose(e);
    breakSekichu(e);
    W(e)->cycleTimer--;
    if (W(e)->cycleTimer != 0) {
        return;
    }
    W(e)->cycleTimer = 0x1e;
    func_02085f98(e, 0x59);
}

// em29_init (0x020418bc): sets the start action and offsets from the type, resets the cycle timer, then
// centres the scroll position at (0x800, 0x600) and refreshes the scroll arguments.

ARM void em29_init(Entity *e) {
    e->action = 1;
    e->spriteSettings.b0 = 1;
    e->y.HALF.LO = 2 - e->type;
    e->z.HALF.HI = data_020d346c[e->type];
    W(e)->cycleTimer = 0x1e;
    if (e->type != 0) {
        if (e->type == 1) {
            e->unk_5e.b0 = 3;
        }
    } else {
        e->spriteSettings.b14 = 1;
        e->spriteSettings.b30 = 1;
    }
    moveInit(e);
    InitAnimationForceUpdate(e, 0);
    func_02085cf8(e);
    W(e)->subPosX = 0x800;
    W(e)->subPosY = 0x600;
    data_0212c574[0] = W(e)->subPosX;
    data_0212c574[1] = W(e)->subPosY;
    data_0212c574[2] = 0;
    ObjAffineSet2(data_0212c574, e);
}

// em29_move (0x02041a3c): when the parent is in state 1 this switches to action 3. Otherwise a
// follower copies the parent's position, while the first type nudges itself by the packed offset for this frame.
// A child records the offset it has just moved by, in its own table.
