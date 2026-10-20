#include "engine/functions.h"
#include "global.h"
#include "object/nemoto_3.h"

// nemoto family (module nemoto), 0x0206d350 .. 0x0206d3fc.
// Address -> name: 0x0206d350 nemoto_writecell, 0x0206d3d0 nemoto_rewritecell

ARM void nemoto_writecell(Entity *e) {
    Vars_NemotoCell *v = VARS(Vars_NemotoCell, e);

    v->cell = ((e->x.HALF.HI - data_0212c648.originX) >> 4) | (((e->y.HALF.HI - data_0212c648.originY) >> 4) << 6);
    v->cellValue = func_0208367c(v->cell, e->layer);
    v->cellFlag = func_02083d4c(v->cell, e->layer);
    func_0208366c(0x4009, v->cell, e->layer);
    func_0208365c(0xf, v->cell, e->layer);
}

ARM void nemoto_rewritecell(Entity *e) {
    Vars_NemotoCell *v = VARS(Vars_NemotoCell, e);

    func_0208366c(v->cellValue, v->cell, e->layer);
    func_0208365c(v->cellFlag, v->cell, e->layer);
}
