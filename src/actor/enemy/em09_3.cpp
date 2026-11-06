#include "engine/functions.h"
#include "engine/player.h"
#include "actor/enemy/em09.h"
#include "global.h"

// Functions in this file (module em09, the kuttsuki partner of the boss):
//   em09_kuttsuki (0x0203a75c)

// em09_kuttsuki(OBJ_WORK_*): the boss holds its child (the partner player's kuttsuki); while the child is alive and
// its time limit (subtimer) has not run out, the child is positioned and the rupee drop counts down, otherwise the
// kuttsuki reset runs.
void em09_kuttsuki(Entity *e) {
    void *app;
    Entity *partner;
    Entity *target;
    u8 index;

    seqMove(e);
    seqMove(e);
    if (playerKeys[e->child->type] != 0) {
        e->subtimer++;
    }
    app = KnifeApp_getInstance();
    target = e->child;
    partner = data_0212c7d4[e->child->type];
    if (KnifeApp_isWirelessMode(app) == 0 && partner == NULL) {
        index = e->child->type ^ 1;
        if (data_0212c7d4[index] != NULL) {
            partner = data_0212c7d4[index];
            target = playerWork[index].entity;
        }
    }
    if (e->subtimer > 0x37 || partner == NULL || e->child->health == 0) {
        kuttsukiReset(e);
        return;
    }
    func_0208919c(e->child);
    playerWork[e->child->type].unk_1a |= 0x80;
    ObjPosCopyOfs32(e, e->child, 0, 1);
    e->child->z.HALF.HI = data_020d1d96[e->frame & 7];
    e->child->unk_2e = 0;
    VBT(e)->latchTimer--;
    if (VBT(e)->latchTimer != 0) {
        return;
    }
    VBT(e)->latchTimer = 0x2d;
    AddRupee(target, data_020d1d93[e->type]);
    SoundReq(0x95);
}
