#include "engine/functions.h"
#include "actor/object/tama0f.h"
#include "actor/object/tama0f_decls.h"
#include "global.h"

// tama0f_contact (0x0207d1f4): runs the action, then handles a contact (bit 7 of contactFlags) for a non-zero type2.
// Contact kind 0 attaches a work object to the touching player (status bit 0x400); kind 1 spawns rupees by type2;
// kinds 4, 8 and 12 spawn rupees, an item, or damage the actor depending on type2.
void tama0f_contact(Entity *e) {
    data_020dcb48[e->action](e);
    if (e->type2 == 0) {
        return;
    }
    if (!(e->contactFlags & 0x80)) {
        return;
    }
    switch (e->contactFlags & 0x7f) {
        case 0:
            if (!(playerWork[e->contactedEntity->type].statusFlags & 0x400)) {
                Entity *child = GetSetWork(0x55, 1, 0);
                if (child != NULL) {
                    child->child = e->contactedEntity;
                    playerWork[e->contactedEntity->type].statusFlags |= 0x400;
                }
            }
            if (e->type2 == 1) {
                PutObjWork(e);
            }
            break;
        case 1:
            switch (e->type2) {
                case 1:
                    tama0f_ruppyset(e, 3);
                    PutObjWork(e);
                    break;
                case 2:
                    tama0f_ruppyset(e, 2);
                    PutObjWork(e);
                    break;
            }
            break;
        case 4:
        case 8:
        case 12:
            switch (e->type2) {
                case 3:
                    if (e->parent->action == 5) {
                        e->iframes = 0x10;
                        if (VARS(Vars_Tama0f, e)->fireTimer != 0 && e->health != 0) {
                            SoundReq(0x2d);
                            e->health -= 4;
                        } else {
                            e->health = 0;
                        }
                    }
                    break;
                case 1:
                    tama0f_ruppyset(e, 1);
                    PutObjWork(e);
                    break;
                case 2:
                    if (Random() & 0xf) {
                        ItemSet(e, 0);
                    } else {
                        ItemSet(e, 7);
                    }
                    PutObjWork(e);
                    break;
            }
            break;
    }
}
