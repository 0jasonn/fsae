#include "engine/functions.h"
#include "global.h"
#include "enemy/em21.h"
#include "enemy/em21_2.h"

// Functions in this file: Em22 (0x0203f740, dsd Em22, entry of em22).

ARM void Em22(Entity *e) {
    EnemyFunctionHandler(e, em22_stateTable);
}
