#include "engine/functions.h"
#include "global.h"
#include "object/set66.h"

// Set67 actor, second unit (module set67). Address -> name:
//   0x02075604 set67_animSingleFrame (provisional name; tail call to UpdateAnimationSingleFrame)

ARM void set67_animSingleFrame(Entity *e) {
    UpdateAnimationSingleFrame(e);
}
