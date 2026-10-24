#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/a_decls.h"

// Front check (module frontcheck, second unit). Original names from the debug build: setmoveblock, openDoor.

// Sets the move block at cell for the kind/mode pair: kinds 0x131..0x135 each take one mode value (or any mode).
ARM void SetMoveBlockByKind(Entity *e, u8 mode, s32 kind, u16 cell) {
    switch (kind) {
    case 0x131:
        setmoveblock(e, cell, mode);
        break;
    case 0x132:
        if (mode == 0) {
            setmoveblock(e, cell, mode);
        }
        break;
    case 0x135:
        if (mode == 8) {
            setmoveblock(e, cell, mode);
        }
        break;
    case 0x133:
        if (mode == 0x10) {
            setmoveblock(e, cell, mode);
        }
        break;
    case 0x134:
        if (mode == 0x18) {
            setmoveblock(e, cell, mode);
        }
        break;
    }
}
