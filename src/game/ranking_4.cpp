#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"

// Ranking table accessors. Address -> name:
//   0x0205610c ranking_getKey (provisional, reads the sort key byte of entry 'index' of data_02171d00)
//   0x0205611c ranking_noop (provisional, empty function)

ARM u8 ranking_getKey(u8 index) {
    return data_02171d01[index * 4];
}

ARM void ranking_noop(void) {
}
