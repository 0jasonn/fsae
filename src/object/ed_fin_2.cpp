#include "engine/functions.h"
#include "global.h"
#include "object/c_decls.h"

// Ending fin actor, init and move (module ed_fin). Address -> name:
//   0x0205f868 fin_init (name from symbols.txt)
//   0x0205f8e4 fin_move (name from symbols.txt)
//   (Set5b at 0x0205f928 is in the next unit)

// Scale of the fin, kept in the actor fields past the shared header
typedef struct Vars_Fin {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u16 scaleX;
    /* 72 */ u16 scaleY;
} Vars_Fin;

extern KnifeObjAffineSrcData scrollArgs; // affine source for ObjAffineSet2 (named in symbols.txt)

ARM void fin_init(Entity *e) {
    Vars_Fin *v = VARS(Vars_Fin, e);
    u8 action = e->action + 1;

    e->spriteSettings.b0 = 1;
    e->spriteSettings.b30 = 0;
    e->action = action;
    e->spriteSettings.b14 = 0;
    e->x.HALF.HI = 0x80;
    e->y.HALF.HI = 0xd0;
    func_02085cf8(e);

    v->scaleX = 0x100;
    v->scaleY = 0x800;
    scrollArgs.data[0] = v->scaleX;
    scrollArgs.data[1] = v->scaleY;
    scrollArgs.data[2] = 0;
    ObjAffineSet2(&scrollArgs, e);
}

ARM void fin_move(Entity *e) {
    Vars_Fin *v = VARS(Vars_Fin, e);
    u16 scaleY = v->scaleY;
    u16 scaleX;

    if (scaleY <= 0x100) {
        return;
    }
    scaleX = v->scaleX; // read before the store, as the original does
    v->scaleY = scaleY - 0x20;
    scrollArgs.data[0] = v->scaleX;
    scrollArgs.data[1] = v->scaleY;
    scrollArgs.data[2] = 0;
    ObjAffineSet2(&scrollArgs, e);
}
