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

// FAKE MATCH: Random takes no argument, but these call sites only match when a value is in r0 at the call.
// Revisit once the real source shape is known (see docs/nonmatching/fake_random_arg.md).
#define RANDOM_WITH_ARG(x) (((u32 (*)(u32))Random)((u32)(x)))

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
ARM void em30_type0_init(Entity *e) {
    if (setUde(e) == 0) {
        return;
    }
    e->action = 1;
    e->timer = 0x78;
    e->spriteSettings.b0 = 1;
    e->unk_2e = 8;
    e->unk_5e.b2 = 3;
    e->unk_3c |= 0x80;
    e->unk_6c[4] = e->direction;
    e->hitbox = data_020d34e2;
    e->unk_6c[6] = 1;
    InitAnimationForceUpdate(e, 0);
}
// em30_type0_wait (0x02042398): when the timer runs out, picks a turn sign from the direction, takes a
// remainder with a table value per player count, and goes to action 2 or 5 from the parent's flag bit for the type.

ARM void em30_type0_wait(Entity *e) {
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    int sign = (e->direction > 0x80) ? 1 : -1;
    e->unk_6c[5] = sign;
    e->unk_6c[7] = ((u32)RANDOM_WITH_ARG(sign) % data_020f26c0[data_0212c7c8.unk_0 - 2]) << 1;
    if (e->parent->unk_6c[4] & data_020cf9b8[e->type2]) {
        e->action = 2;
    } else {
        e->action = 5;
    }
}
// type0_attackBlossom (0x02042818): counts the phase timer down. Above 0x5a the parts animate with bit 0x80 set
// when they are in play. Between 0x1e and 0x5a the bit is cleared. At 0x1e the bit is set again. At 0 this entity
// goes to action 0xc and both parts restart their animations.
