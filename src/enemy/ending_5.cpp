#include "engine/functions.h"
#include "enemy/ending.h"
#include "global.h"

// Implementer B, round 6: yousei_move (0x020457a8), finale_end (0x0204581c).

// yousei_move (0x020457a8): starts the fairy movement on the three scene slots and plays sound 0x201.
ARM void yousei_move(void) {
    ObjAnimMoveSet(SCENE_SLOT(1).entity, youseiBounds1, 0x78);
    SCENE_SLOT(1).entity->action = 1;
    ObjAnimMoveSet(SCENE_SLOT(2).entity, youseiBounds2, 0x78);
    SCENE_SLOT(2).entity->action = 1;
    ObjAnimMoveSet(SCENE_SLOT(3).entity, youseiBounds3, 0x78);
    SCENE_SLOT(3).entity->action = 1;
    SoundReq(0x201);
}

// finale_end (0x0204581c): clears the screen and starts the next task chain step once the blend is idle.
ARM void finale_end(void) {
    if (data_0212c5ac.blendEnabled != 0) {
        return;
    }
    DispReset();
    *(u16 *)0x05000000 = 0;
    data_021355a0 = 0;
    func_02082c54(0);
    finalizeVirtualScreenData();
    ObjWorkPoolClear();
    ObjMoveInit();
    Task_Chain(6);
    func_020827a8(5);
}
