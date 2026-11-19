#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/a_decls.h"

// Fields of the door object that openDoor sets.
typedef struct Vars_OpenDoor {
    /* 00 */ u8 unk_00[0x7e];
    /* 7e */ u16 openPhase;
} Vars_OpenDoor;

// openDoor (0x0202375c): the block pushed by the player opens a door object. The door takes the position of the actor
// plus the table offset for the facing bits of the player, and the cell under the door is cleared in the background
// buffer.
void openDoor(Entity *e, PlayerData *pl, BG_BUFF_ *bg) {
    Entity *door;
    u32 cell;

    door = GetObjWork();
    if (door == NULL) {
        return;
    }
    door->objKind = 6;
    door->objId = 8;
    door->type2 = (pl->unk_35 >> 1) | 0x80;
    door->x.HALF.HI = e->x.HALF.HI + data_020cd6e4[(door->type2 & 3) * 2];
    door->y.HALF.HI = e->y.HALF.HI + data_020cd6e4[(door->type2 & 3) * 2 + 1];
    VARS(Vars_OpenDoor, door)->openPhase = 2;
    cell = ((door->x.HALF.HI - mapState.originX) >> 4) | (((door->y.HALF.HI - mapState.originY) >> 4) << 6);
    ((u16 *)bg)[cell + 2] = 0;
    RegistObjWork(6, door);
}
