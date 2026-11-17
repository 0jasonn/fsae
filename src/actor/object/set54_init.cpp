#include "engine/functions.h"
#include "actor/object/pot.h"
#include "actor/object/objdecls.h"

// set54_init, 0x02071b00. Starts the action, picks the door sprite row from the door type, and asks the map cell
// under the object to be rewritten.
void set54_init(Entity *e) {
    e->action = 1;
    e->timer = 4;
    e->type2 = DoorTypeCheck(e) * 0x18;
    func_0208366c(0, MAP_CELL_INDEX(e->x.HALF.HI, e->y.HALF.HI), e->layer);
}
