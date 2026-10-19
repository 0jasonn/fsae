#include "engine/functions.h"
// Functions in this file:
//   RankCheck -> RankCheck
//   CheckCubeKaitengiri -> CheckCubeKaitengiri
//   CheckKenBeam -> CheckKenBeam
#include "game/gamestateview_c.h"
#include "engine/entity.h"
#include "global.h"

ARM int RankCheck(void) {
    switch (data_0212c7c8.difficulty) {
        case 1:
            if (data_0212c7c8.score >= 0x3e8) {
                return 1;
            }
        case 2:
            if (data_0212c7c8.score >= 0xbb8) {
                return 2;
            }
        case 3:
            if (data_0212c7c8.score >= 0x1388) {
                return 3;
            }
    }
    return 0;
}

ARM BOOL CheckCubeKaitengiri(Entity *e) {
    return (data_0212c7f0[e->type].flags & 2) != 0;
}

ARM BOOL CheckKenBeam(Entity *e) {
    return (data_0212c7f0[e->type].flags & 1) != 0;
}
