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
ARM BOOL setUde(Entity *e) {
    Entity *a;
    Entity *b;
    if ((a = GetObjWork()) != NULL && (b = GetObjWork2()) != NULL) {
        a->unk_08 = 3;
        b->unk_08 = 3;
        a->unk_09 = 0x30;
        b->unk_09 = 0x30;
        a->type = 3;
        b->type = 3;
        a->type2 = 2;
        b->type2 = 3;
        a->parent = e->parent;
        b->parent = e->parent;
        a->child = e;
        b->child = e;
        b->unk_6c[4] = e->direction;
        ObjPosCopy(e, a);
        ObjPosCopy(e, b);
        RegistObjWork(4, a);
        RegistObjWork(4, b);
        return TRUE;
    }
    return FALSE;
}

// setFlower (0x02042cc8): like setUde with different types and directions. Stores the
// two parts in this entity's part slots and plays sound 0xa2.

ARM int setFlower(Entity *e) {
    Entity *a;
    Entity *b;
    if ((a = GetObjWork()) != NULL && (b = GetObjWork2()) != NULL) {
        a->unk_08 = 3;
        b->unk_08 = 3;
        a->unk_09 = 0x30;
        b->unk_09 = 0x30;
        a->type = 1;
        b->type = 2;
        a->parent = e->parent;
        b->parent = e->parent;
        a->child = e;
        b->child = e;
        ObjPosCopy(e, a);
        ObjPosCopy(e, b);
        RegistObjWork(4, a);
        RegistObjWork(4, b);
        VPARTS(e)->partA = a;
        VPARTS(e)->partB = b;
        EnqueueSFX(0xa2);
        return 1;
    }
    return 0;
}
// Enemy_SetSpriteFromTable (0x02042d7c): picks the sprite index from data_020f26c3 by the child's state and this type,
// and copies it into the second sprite index field.

ARM void Enemy_SetSpriteFromTable(Entity *e) {
    e->spriteSettings.b20 = data_020f26c3[e->child->unk_6c[7] + e->type - 1];
    e->spriteSettings.b16 = e->spriteSettings.b20;
}

// flowerTamaSet (0x02042f30): picks one of three spawn groups at random. Group 0 makes three type-2 parts
// (the two side ones are offset from this entity), group 1 makes three type-3 parts, and group 2 makes four type-1
// parts placed at this entity's position and plays sound 0x9f.
