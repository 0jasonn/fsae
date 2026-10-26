#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "enemy/decls_b2.h"

// Functions in this file (module igoal, original names from the debug build):
//   yukaRewCell (yukaRewCell(OBJ_WORK_*)), igoalRewCell (igoalRewCell(OBJ_WORK_*))

extern u8 data_0212c648[]; // base position of the cell grid: u16 at 0x18 (x) and 0x1a (y)

// yukaRewCell (0x0203c044): rewrites the same four cells as igoalRewCell, with the ids and flag of the layer kind
// (layer >> 14 == 2 uses 0x7b..0x7e with flag 0x8000, otherwise 0x52..0x55 with flag 0x4000).
ARM void yukaRewCell(Entity *e) {
    s32 x;
    s32 y;
    s32 cell;

    y = e->y.HALF.HI;
    x = e->x.HALF.HI;
    cell = (u16)(((x - 8 - *(u16 *)(data_0212c648 + 0x18)) >> 4) |
                 (((y - 8 - *(u16 *)(data_0212c648 + 0x1a)) >> 4) << 6));
    if ((e->layer >> 14) != 2) {
        RewCell(0x52, cell, 0x4000);
        RewCell(0x53, cell + 1, 0x4000);
        RewCell(0x54, cell + 0x40, 0x4000);
        RewCell(0x55, cell + 0x41, 0x4000);
    } else {
        RewCell(0x7b, cell, 0x8000);
        RewCell(0x7c, cell + 1, 0x8000);
        RewCell(0x7d, cell + 0x40, 0x8000);
        RewCell(0x7e, cell + 0x41, 0x8000);
    }
}

// igoalRewCell (0x0203c158): rewrites the four cells covered by the 16x16 object at the entity position, one id each
// (0x152 to 0x155, the second row of ids starts 0x40 cells down), with the entity's layer.
ARM void igoalRewCell(Entity *e) {
    s32 x;
    s32 y;
    s32 cell;

    y = e->y.HALF.HI;
    x = e->x.HALF.HI;
    cell = (u16)(((x - 8 - *(u16 *)(data_0212c648 + 0x18)) >> 4) |
                 (((y - 8 - *(u16 *)(data_0212c648 + 0x1a)) >> 4) << 6));
    RewCell(0x152, cell, e->layer);
    RewCell(0x153, cell + 1, e->layer);
    RewCell(0x154, cell + 0x40, e->layer);
    RewCell(0x155, cell + 0x41, e->layer);
}
