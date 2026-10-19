#include "engine/functions.h"
#include "global.h"
#include "object/objdecls.h"

// Set53 and Set54 actors (module set54). Address -> name:
//   0x02071a70 set53_scrcheck (original name; returns the offset index of the first free check point)
//   0x02071ae0 set53_nop (no-op action, provisional name)
//   0x02071ae4 Set54 (original name)
//   set54_init (0x02071b00), set54_open (0x02071b6c), set54_move (0x02071bec) are in scratch/agentD/nonmatching

extern const s8 set53_scrcheckOffsets[]; // (dx, dy) pairs, indexed by direction index
extern const EntityFunc set54_actions[]; // indexed by e->action

ARM u8 set53_scrcheck(Entity *e, Entity *other, u8 flag) {
    u8 idx;
    u8 dir;

    dir = e->animationState;
    if (flag == 0) {
        dir ^= 4;
    }
    idx = (dir + 2) & 6;
    if (func_02083d18(other, set53_scrcheckOffsets[idx], set53_scrcheckOffsets[idx + 1])) {
        do {
            idx = (idx + 2) & 6;
        } while (func_02083d18(other, set53_scrcheckOffsets[idx], set53_scrcheckOffsets[idx + 1]));
    }
    return idx << 2;
}

ARM void set53_nop(Entity *e) {
}

ARM void Set54(Entity *e) {
    set54_actions[e->action](e);
}
