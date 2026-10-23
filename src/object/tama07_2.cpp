#include "engine/functions.h"
#include "object/tama07.h"

// tama07 family, address -> name (original names from symbols.txt; the name of tama07_remove is a guess):
//   0x0207f830 tama07_remove

// tama07_remove, 0x0207f830 (name a guess). Clears the parent's link to this actor and removes it.
ARM void tama07_remove(Entity *e) {
    if (e->parent != 0) {
        e->parent->child = 0;
    }
    PutObjWork(e);
}
