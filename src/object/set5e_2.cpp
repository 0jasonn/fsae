#include "engine/functions.h"
#include "global.h"

// Set5e actor, second unit (module set5e). Address -> name:
//   0x02060050 set5e_move (original name)

typedef struct Vars_Set5e {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u16 lastValue; // value seen at the last check
    /* 7c */ const u16 *valuePtr; // points at the value to compare against
} Vars_Set5e;

ARM void set5e_move(Entity *e) {
    Entity *obj;

    if (VARS(Vars_Set5e, e)->lastValue == *VARS(Vars_Set5e, e)->valuePtr) {
        return;
    }
    if (e->type == 0xe) {
        obj = GetObjWork();
        if (obj != NULL) {
            obj->objKind = 8;
            obj->objId = 4;
            obj->type = 0xff;
            ObjPosCopy(e, obj);
            obj->x.HALF.HI = e->x.HALF.HI;
            obj->y.HALF.HI = e->y.HALF.HI;
            obj->unk_5e.b0 = 0;
            RegistObjWork(2, obj);
        }
        PutObjWork(e);
        return;
    }
    obj = GetSetWork(0, e->type, 1);
    if (obj != NULL) {
        ObjPosCopy(e, obj);
    }
    PutObjWork(e);
}
