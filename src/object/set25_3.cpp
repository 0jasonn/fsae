#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/set25.h"
#include "object/set25_3.h"

// Set25 family, third unit (module set25). Address -> name:
//   0x0206677c kudakeSet (parked in scratch/agentC/nonmatching, register allocation differs)
//   0x02066818 vitaldec (original name vitaldec(OBJ_WORK_*, unsigned char*))

typedef struct Vars_Vitaldec {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 recellDone; // set once recell0 has run for this actor (low health)
} Vars_Vitaldec;

// Applies the contact damage of the other entity to this one and reacts to it
ARM void vitaldec(Entity *e, u8 *timer) {
    Entity *other;
    u8 damage;
    u8 health;

    other = e->contactedEntity;
    if (other->unk_40 >= 0x24) {
        return;
    }
    damage = data_020da4ec[other->unk_40];
    if (damage == 0) {
        return;
    }
    *timer = 8;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        if (Knife_Single_SinglePlay_GetInstance()[1] != 0) {
            if (data_0212ceb0[0].entity->unk_21 == data_0212ceb0[1].entity->unk_21) {
                damage = damage << 1;
            }
        }
    }
    if (damage > e->health) {
        e->health = 0;
    } else {
        e->health = e->health - damage;
    }
    health = e->health;
    if (health != 0) {
        if (VARS(Vars_Vitaldec, e)->recellDone == 0 && health < 0x32) {
            recell0(e);
            VARS(Vars_Vitaldec, e)->recellDone = 1;
        }
        kudakeSet(e);
    } else {
        e->action = e->action + 1;
        e->timer = 0;
        e->subtimer = (e->type + 1) * 2;
        e->statusFlags = e->statusFlags & 0x7f;
    }
}
