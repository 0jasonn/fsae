#include "engine/functions.h"
#include "engine/player.h"
#include "object/set29.h"
#include "global.h"

extern EntityFunc set29StateTable[];
extern const u8 set29TypeTable[];

// Set29 (0x02068bd8): runs the state function for the current action.
ARM void Set29(Entity *e) {
    set29StateTable[e->action](e);
}
