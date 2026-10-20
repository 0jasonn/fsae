#include "engine/functions.h"
#include "global.h"
#include "object/objdecls.h"
#include "object/set58.h"

// Set58 youseidama update (module set58). Address -> name:
//   0x02073984 youseidama_up (original name)
//   0x02073a18 youseidama_move (original name)

ARM void youseidama_up(Entity *e) {
    UpdateAnimationSingleFrame(e);
    e->z.WORD -= 0x8000;
    if (e->z.HALF.HI == -20) {
        e->action = 2;
        SoundReq(func_02081b64() != 0 ? 0x23a : 0x214);
        return;
    }
    if (e->z.HALF.HI != -10 || e->subtimer != 0) {
        return;
    }
    {
        Entity *child = GetSetWork(0x58, 5, 0);
        if (child == NULL) {
            return;
        }
        ObjPosCopyOfs32(e, child, 0, 0x40000);
    }
    e->subtimer = 1;
}

ARM void youseidama_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    setYouseiEffect(e);
    if (em12_typeMasks & 1) {
        PutObjWork(e);
    }
}
