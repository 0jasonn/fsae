#include "engine/functions.h"
#include "global.h"
#include "object/set66.h"

// Set67 actor (module set67). Address -> name:
//   0x020755a4 Set67 (provisional name; dispatches on e->action)
//   0x02075604 set67_animSingleFrame (provisional name; tail call to UpdateAnimationSingleFrame)

ARM void Set67(Entity *e) {
    set67_actions[e->action](e);
}
