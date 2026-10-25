#include "engine/functions.h"
#include "engine/objwork.h"
#include "global.h"

// Set work helpers (module setwork). Address -> name:
//   0x02076858 GetSetWork (original name)
//   0x02076898 GetSetWorkSp (original name)
//   0x020768d8 KemuriSet (original name)
//   0x02076904 SKemuriSet (original name)
//   0x02076930 HajikeSet (original name)
//   0x0207695c MizupochaSet (original name)
//   0x02076988 BikkuriSet (original name)
//   0x020769d4 ItemSet (original name)

ARM Entity *GetSetWork(s32 kind, s32 type, s32 type2) {
    Entity *e;

    e = GetObjWork();
    if (e != NULL) {
        e->objKind = 6;
        e->objId = kind;
        e->type = type;
        e->type2 = type2;
        RegistObjWork(6, e);
    }
    return e;
}

ARM Entity *GetSetWorkSp(u8 kind, u8 type, u8 type2) {
    Entity *e;

    e = GetObjWorkSp();
    if (e != NULL) {
        e->objKind = 6;
        e->objId = kind;
        e->type = type;
        e->type2 = type2;
        RegistObjWork(6, e);
    }
    return e;
}

ARM void KemuriSet(Entity *e) {
    Entity *spawn;

    spawn = GetSetWork(0xf, 2, 0);
    if (spawn == NULL) {
        return;
    }
    ObjPosCopy(e, spawn);
}

ARM void SKemuriSet(Entity *e) {
    Entity *spawn;

    spawn = GetSetWork(0xf, 0x11, 0);
    if (spawn == NULL) {
        return;
    }
    ObjPosCopy(e, spawn);
}

ARM void HajikeSet(Entity *e) {
    Entity *spawn;

    spawn = GetSetWork(0xf, 6, 0);
    if (spawn == NULL) {
        return;
    }
    ObjPosCopy(e, spawn);
}

ARM void MizupochaSet(Entity *e) {
    Entity *spawn;

    spawn = GetSetWork(0xf, 0xb, 0);
    if (spawn == NULL) {
        return;
    }
    ObjPosCopy(e, spawn);
}

ARM void BikkuriSet(Entity *e, s32 a, s32 b) {
    Entity *spawn;

    spawn = GetSetWork(0xf, 0x18, 0x20);
    if (spawn == NULL) {
        return;
    }
    ObjPosCopyOfs32(e, spawn, (s16)a << 16, (s16)b << 16);
}

ARM Entity *ItemSet(Entity *e, u8 id) {
    Entity *spawn;

    spawn = GetSetWork(0, 0, 0);
    if (spawn != NULL) {
        spawn->x.WORD = e->x.WORD;
        spawn->y.WORD = e->y.WORD;
        spawn->type = id;
        spawn->layer = e->layer;
        func_0208ae78(spawn);
    }
    return spawn;
}
