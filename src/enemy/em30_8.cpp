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

extern const EntityFunc em29_stateTable[];
extern const u16 em29_scrollLimitsIn[];
extern const s8 em29_restZ[];
extern const s8 em29_sinkZ[];
extern const u16 em29_scrollLimitsOut[];
extern u8 encntSharedState[];
extern const u8 em31_typeFx[];
extern const u8 em31_randomFx[];
extern const EntityFunc em31_stateTable[];
extern const EntityFunc em31_handlerTable[];
extern const u8 em30_type0Hitbox[];

// Em29 (0x020417e8): a follower whose parent raises trigger bit 0 restarts in action 6.
// Then runs the action handler and, for type 2, the two helpers below and a 0x1e-frame cycle that plays sound 0x59.
ARM BOOL setUde(Entity *e) {
    Entity *first;
    Entity *second;
    if ((first = GetObjWork()) != NULL && (second = GetObjWork2(first)) != NULL) {
        first->objKind = 3;
        second->objKind = 3;
        first->objId = 0x30;
        second->objId = 0x30;
        first->type = 3;
        second->type = 3;
        first->type2 = 2;
        second->type2 = 3;
        first->parent = e->parent;
        second->parent = e->parent;
        first->child = e;
        second->child = e;
        second->unk_6c[4] = e->direction;
        ObjPosCopy(e, first);
        ObjPosCopy(e, second);
        RegistObjWork(4, first);
        RegistObjWork(4, second);
        return TRUE;
    }
    return FALSE;
}

// setFlower (0x02042cc8): like setUde with different types and directions. Stores the
// two parts in this entity's part slots and plays sound 0xa2.

ARM int setFlower(Entity *e) {
    Entity *first;
    Entity *second;
    if ((first = GetObjWork()) != NULL && (second = GetObjWork2(first)) != NULL) {
        first->objKind = 3;
        second->objKind = 3;
        first->objId = 0x30;
        second->objId = 0x30;
        first->type = 1;
        second->type = 2;
        first->parent = e->parent;
        second->parent = e->parent;
        first->child = e;
        second->child = e;
        ObjPosCopy(e, first);
        ObjPosCopy(e, second);
        RegistObjWork(4, first);
        RegistObjWork(4, second);
        VPARTS(e)->partA = first;
        VPARTS(e)->partB = second;
        EnqueueSFX(0xa2);
        return 1;
    }
    return 0;
}
// Enemy_SetSpriteFromTable (0x02042d7c): picks the sprite index from em30_spriteTable by the child's state and this type,
// and copies it into the second sprite index field.

ARM void Enemy_SetSpriteFromTable(Entity *e) {
    e->spriteSettings.b20 = em30_spriteTable[e->child->unk_6c[7] + e->type - 1];
    e->spriteSettings.b16 = e->spriteSettings.b20;
}

// flowerTamaSet (0x02042f30): picks one of three spawn groups at random. Group 0 makes three type-2 parts
// (the two side ones are offset from this entity), group 1 makes three type-3 parts, and group 2 makes four type-1
// parts placed at this entity's position and plays sound 0x9f.
