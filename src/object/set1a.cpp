#include "engine/functions.h"
#include "object/set1a.h"
#include "global.h"

// Set1a actor and flag helpers (module set1a). Address -> name:
//   0x020591a4 Set1a (original name)
//   0x020591c0 set1a_noop0, 0x020591c4 set1a_noop1, 0x020591c8 set1a_noop2 (provisional, empty handlers)
//   0x020591cc set1a_typeDispatch (provisional, set1a_typeActions[e->type](e))
//   0x020591e8 check_flag (original name)
//   0x02059224 check_next (original name)

ARM void Set1a(Entity *e) {
    set1a_actions[e->action](e);
}

ARM void set1a_noop0(Entity *e) {
}

ARM void set1a_noop1(Entity *e) {
}

ARM void set1a_noop2(Entity *e) {
}

ARM void set1a_typeDispatch(Entity *e) {
    set1a_typeActions[e->type](e);
}

ARM int check_flag(unsigned long mask, unsigned char start, unsigned char count) {
    int result = 1;
    int end = start + count;
    unsigned char i = start;
    if (i < end) {
        do {
            if ((mask & (1 << i)) == 0) {
                result = 0;
            }
            i++;
        } while (i < end);
    }
    return result;
}

ARM int check_next(unsigned long mask, unsigned char start, unsigned char count) {
    int end = start + count;
    unsigned char i;
    for (i = start; i < end; i++) {
        if (mask & (1 << i)) {
            return 1;
        }
    }
    return 0;
}
