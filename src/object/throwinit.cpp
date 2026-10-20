#include "engine/functions.h"
#include "global.h"
#include "object/tama11.h"

// throw module, 0x02080b54 to 0x02080ca4 (the throwinit actor state and its dispatcher).
//   tama11_putObjWorkThunk (0x02080b54): tail call to PutObjWork.
//   throwinit (0x02080b60): sets up the throw from the child's position and copies the child's and player's pose.

// tama11_putObjWorkThunk (0x02080b54)
ARM void tama11_putObjWorkThunk(Entity *e) {
    ((void (*)(Entity *))PutObjWork)(e);
}
