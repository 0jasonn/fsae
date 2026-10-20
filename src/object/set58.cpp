#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/objdecls.h"
#include "object/set58.h"

// Set58 actor (module set58). Address -> name:
//   0x02073390 Set58 (provisional name; dispatches on e->type)
//   0x020733ac set58_body (original name; dispatches on e->action)
//   0x020733c8 body_init (original name)
//   0x020734a4 body_sazanami is in scratch/agentD/nonmatching (near miss)

ARM void Set58(Entity *e) {
    set58_typeActions[e->type](e);
}

ARM void set58_body(Entity *e) {
    set58_bodyActions[e->action](e);
}

ARM void body_init(Entity *e) {
    set58_actionInit(e);
    set58_bodyState[0x30] = 0xff;
    set58_bodyState[0x31] = 0xff;
    set58_bodyState[0x32] = 0;
    set58_bodyState[0x34] = 0xff;
    set58_bodyState[0x35] = 0xff;
    set58_bodyState[0x36] = 0;
    e->timer = 0;
    V58(e)->unk_7c = 0x122;
    em12_typeMasks = 0;
    if (e->type == 0xb) {
        CgLoad(set58_cgIdsA[*((u8 *)&data_0212c7c8 + 1)]);
        return;
    }
    if (func_02081b64() != 0) {
        Entity *child = GetSetWork(0x58, 0xb, 0);
        if (child == NULL) {
            return;
        }
        ObjPosCopyOfs32(e, child, 0, 0);
        PutObjWork(e);
    } else {
        CgLoad(set58_cgIdsB[*((u8 *)&data_0212c7c8 + 1)]);
    }
}
