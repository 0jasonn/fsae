#include "engine/functions.h"
// Functions in this file:
//   RankCheck -> RankCheck
//   CheckCubeKaitengiri -> CheckCubeKaitengiri
//   CheckKenBeam -> CheckKenBeam
#include "game/player_flags.h"
#include "engine/entity.h"
#include "global.h"

int RankCheck(void) {
    switch (gameState.level) {
        case 1:
            if (gameState.score >= 0x3e8) {
                return 1;
            }
        case 2:
            if (gameState.score >= 0xbb8) {
                return 2;
            }
        case 3:
            if (gameState.score >= 0x1388) {
                return 3;
            }
    }
    return 0;
}

BOOL CheckCubeKaitengiri(Entity *e) {
    return (enemyTypeFlags[e->type].flags & 2) != 0;
}

BOOL CheckKenBeam(Entity *e) {
    return (enemyTypeFlags[e->type].flags & 1) != 0;
}
