#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   MoveDir

// Direction step table: dy for each direction at index dir * 8, dx at index dir * 8 + 0x40
extern const s16 trigTable[];

// Moves the entity one step of its speed in its direction (the 0x80 flag of the direction byte stops it)
ARM void MoveDir(Entity *e) {
    if (e->direction & 0x80) {
        return;
    }
    e->x.WORD += e->speed * trigTable[e->direction * 8];
    e->y.WORD -= e->speed * trigTable[e->direction * 8 + 0x40];
}
