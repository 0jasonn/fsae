#include "engine/functions.h"
#include "global.h"

// Ending fairy actor, empty state handler (module ed_fairy). Address -> name:
//   0x0205f848 ed_fairy_NoOp (empty state handler)
//   (ed_fin at 0x0205f84c is in the next unit)

ARM void ed_fairy_NoOp(Entity *e) {
}
