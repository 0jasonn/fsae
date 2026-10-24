#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional names, role not confirmed):
//   Menu_GetPosition (Menu_GetPosition)

// Menu_GetPosition (0x020be9e4): the position value of the object at +4 (its field at +0x10).
extern "C" s32 Menu_GetPosition(void *obj);
ARM s32 Menu_GetPosition(void *obj) {
    u8 *target;

    target = *(u8 **)((u8 *)obj + 4);
    return *(s32 *)(target + 0x10);
}
