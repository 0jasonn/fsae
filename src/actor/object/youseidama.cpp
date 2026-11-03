// Youseidama (fairy ball) actor. Address -> name:
//   0x02073904 youseidama_init (original name)
#include "engine/functions.h"
#include "global.h"
#include "actor/object/objdecls.h"
#include "actor/object/set58.h"

void youseidama_init(Entity *e) {
    Entity *child;
    child = GetSetWork(0x58, 4, 0);
    if (child != NULL) {
        ObjPosCopy(e, child);
        child->parent = e;
        set58_actionInit(e);
        e->subtimer = 0;
        e->spriteSettings.b0 = 1;
    }
    if (func_02081b64() == 0) {
        return;
    }
    e->spriteSettings.b16 = e->spriteSettings.b16 + 1;
}

