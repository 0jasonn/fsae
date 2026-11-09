#include "engine/functions.h"
#include "global.h"
#include "actor/object/object_handlers.h"

// 0x020665dc set25_init (original name)

void set25_init(Entity *e) {
    e->action++;
    e->health = 0x64;
    e->statusFlags = 0x89;
    e->unk_40 = 0x38;
    e->poseId = 0x3e;
    e->hitbox = set25_hitboxTable[e->type];
    e->unk_5c = 0x21aa;
}
