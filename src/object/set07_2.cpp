#include "engine/functions.h"
#include "global.h"

// Set07 actor, moving unit (module set07). Address -> name:
//   0x020617e4 set07_move (original name)

void writeCell(Entity *e);

ARM void set07_move(Entity *e) {
    MoveDir(e);
    func_02085d78(e);
    e->timer--;
    if (e->timer == 0) {
        writeCell(e);
    }
}
