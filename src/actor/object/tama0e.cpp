#include "engine/functions.h"
#include "ui/stagesel_common.h"
#include "global.h"

// Tama0e (0x0207d10c): starts on its first action; a hard contact (damage above 6) bursts it (HajikeSet), spawns a
// child until the game frame counter reaches 0x8ca0 and removes it. Otherwise it is removed when it touches a wall.
void Tama0e(Entity *e) {
    if (e->action == 0) {
        e->action = 1;
        e->spriteSettings.b0 = 1;
        e->hitbox = data_020dcb08;
        InitAnimationForceUpdate(e, (e->direction >> 2) + 0xb);
    }
    if ((e->contactFlags & 0x80) && e->contactedEntity->attackDamage > 6) {
        HajikeSet(e);
        if (gameState.frameCount < 0x8ca0) {
            Entity *child = GetSetWork(0, data_020dcb00[Random() & 7], 1);
            if (child != NULL) {
                ObjPosCopy(e, child);
            }
        }
        PutObjWork(e);
        return;
    }
    func_0208b644(e);
    if (e->wallFlags != 0) {
        PutObjWork(e);
    }
}
