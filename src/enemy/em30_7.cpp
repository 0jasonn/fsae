#include "engine/functions.h"
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

#include "enemy/em29.h"
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
ARM void em30_type1(Entity *e) {
    if (e->action == 0) {
        e->action = 1;
        e->spriteSettings.b0 = 1;
        e->hitbox = data_020d34d2;
        InitAnimationForceUpdate(e, 2);
        Enemy_SetSpriteFromTable(e);
    }
    ObjPosCopyOfs32(e->child, e, 0, 1);
    if (e->frame & 2) {
        if (e->unk_6c[4] != 0) {
            return;
        }
        e->unk_6c[4] = 1;
        EnqueueSFX(0x9c);
    } else {
        e->unk_6c[4] = 0;
    }
}

// em30_type2 (0x02042a5c): on the first action starts action 1 with animation 3 and sets up with
// Enemy_SetSpriteFromTable. Every frame updates the child through ObjPosCopyOfs32.

ARM void em30_type2(Entity *e) {
    if (e->action == 0) {
        e->action = 1;
        e->spriteSettings.b0 = 1;
        e->hitbox = data_020d34ca;
        InitAnimationForceUpdate(e, 3);
        Enemy_SetSpriteFromTable(e);
    }
    ObjPosCopyOfs32(e->child, e, 0, 1);
}
// setUde (0x02042c18): allocates two parts, links both to this entity's parent and to this entity, copies
// this entity's position into each, and registers both. Returns FALSE when either allocation fails.
