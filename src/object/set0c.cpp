#include "engine/functions.h"
#include "object/set0c.h"
#include "global.h"

// Set0c actor (module set0c). Address -> name:
//   0x02058008 set0c_init, 0x020580a4 set0c_appear, 0x0205811c set0c_vanish: not matching yet, see scratch/agentF/nonmatching
//   0x02058078 set0c_wait (original name)

ARM void set0c_wait(Entity *e) {
    if ((VS0C(e)->typeBits & em12_typeMasks[e->areaIndex]) == VS0C(e)->typeBits) {
        e->action++;
    }
}
