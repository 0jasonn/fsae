#include "engine/functions.h"
#include "ui/stagesel_common.h"
#include "global.h"

extern const EntityFunc data_020dcb98[]; // action table of the tama02 family

typedef struct Vars_Tama02 {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *partner; // the object this shot is attached to
} Vars_Tama02;

#define PARTNER(e) (VARS(Vars_Tama02, e)->partner)

// Word at offset 4 of the partner: nonzero while the partner is attached (guess).
#define PARTNER_LINK(partner) (((u32 *)(partner))[1])

// Tama02 (0x0207e0b4): runs the action. While alive and attached it follows its partner; otherwise it releases the
// partner (an object of kind 1 gets its timer reset, a kind 8 id 4 object its low flags cleared) and is removed.
extern "C" {
void Tama02(Entity *e);
}

void Tama02(Entity *e) {
    data_020dcb98[e->action](e);
    if (e->health == 0 || PARTNER_LINK(PARTNER(e)) == 0) {
        if (PARTNER_LINK(PARTNER(e)) != 0) {
            if (PARTNER(e)->objKind == 1) {
                PARTNER(e)->timer = 1;
                PARTNER(e)->zVelocity = 0;
            } else if (PARTNER(e)->objKind == 8 && PARTNER(e)->objId == 4) {
                PARTNER(e)->unk_1a &= 0xf0;
            }
        }
        PARTNER(e)->child = NULL;
        PutObjWork(e);
    } else {
        ObjPosCopy(e, PARTNER(e));
    }
}
