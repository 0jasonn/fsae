#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (provisional name, original function is setActionAnim3):
//   setActionAnim3 -> setActionAnim3

// Sets action 5 and animation 3 of the entity.
ARM void setActionAnim3(Entity *e) {
    e->action = 5;
    e->animationState = 3;
    InitAnimationForceUpdate(e, 3);
}
