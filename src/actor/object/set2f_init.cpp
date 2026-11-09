#include "engine/functions.h"
#include "global.h"
#include "actor/object/object_handlers.h"

// Set2f actor (module set2f), init handler:
//   0x0205af04 set2f_init (original name): sets up the lever entity and registers it in em12_typeMasks

void set2f_init(Entity *e) {
    e->action++;
    e->statusFlags = 0x89;
    e->poseId = 0x39;
    e->unk_5c = 0x20aa;
    e->unk_40 = 0x3f;
    e->hitbox = data_020d8a54;
    if (e->type2 == 0) {
        if ((em12_typeMasks[e->areaIndex] & flagBits[e->type]) != 0) {
            e->type2 = 1;
        } else {
            e->type2 = 0;
        }
    } else {
        em12_typeMasks[e->areaIndex] |= flagBits[e->type];
    }
    rewlever(e);
}
