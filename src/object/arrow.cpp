#include "engine/functions.h"
#include "global.h"
#include "object/arrow.h"

// Arrow actor (module arrow). Original names from the debug build.
//   Arrow

extern const EntityFunc arrow_stateTable[];
extern u8 data_0212c4b8;

// Arrow main: runs the state handler for e->action unless the global freeze flag is set, then the common object update.
ARM void Arrow(Entity *e) {
    if (data_0212c4b8 == 0) {
        arrow_stateTable[e->action](e);
    }
    func_020857c8(e);
}

