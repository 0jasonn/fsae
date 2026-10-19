#include "engine/functions.h"
#include "global.h"

extern EntityFunc oplogo_kenhikariTable[];

ARM void oplogo_kenhikari(Entity *e) {
    oplogo_kenhikariTable[e->action](e);
}
