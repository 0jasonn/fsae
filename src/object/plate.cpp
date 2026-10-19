#include "engine/functions.h"
#include "object/plate.h"
#include "global.h"

// Plate actor (module plate). Address -> name:
//   0x02058684 plate_move (original name)

ARM void plate_move(Entity *e) {
    plate_posY_set(e);
    if (data_0212c4dc == 1) {
        if (VPLATE(e)->count < VPLATE(e)->limit) {
            VPLATE(e)->count++;
        }
    } else if (data_0212c4dc >= 2) {
        VPLATE(e)->count = VPLATE(e)->limit;
    }
    if (data_021349c0[0x27] != 0) {
        PutObjWork(e);
    }
}
