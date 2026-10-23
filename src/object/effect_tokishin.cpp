#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"
#include "object/effectdecls.h"

// effect_tokishin family (module effect_tokishin), 0x0206e2c8 .. 0x0206e2e4 (dispatcher only).
// Address -> name: 0x0206e2c8 effect_tokishin, 0x0206e2e4 effect_tokishin_init, 0x0206e34c effect_tokishin_move

// Action table of effect_tokishin, effectTokishinTable
extern const EntityFunc effectTokishinTable[];

ARM void effect_tokishin(Entity *e) {
    effectTokishinTable[e->action](e);
}
