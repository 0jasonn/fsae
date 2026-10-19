#include "engine/functions.h"
#include "enemy/em2f.h"
#include "global.h"

ARM BOOL setTsubomi(Entity *e) {
    Entity *a;
    Entity *b;
    if ((a = GetObjWork()) != NULL && (b = GetObjWork2(a)) != NULL) {
        a->unk_08 = 3;
        b->unk_08 = 3;
        a->unk_09 = 0x30;
        b->unk_09 = 0x30;
        a->type2 = 0;
        b->type2 = 1;
        a->direction = 0xa0;
        b->direction = 0x60;
        a->parent = e;
        b->parent = e;
        a->child = b;
        b->child = a;
        ObjPosCopy(e, a);
        ObjPosCopy(e, b);
        RegistObjWork(4, a);
        RegistObjWork(4, b);
        return TRUE;
    }
    return FALSE;
}

ARM void tsubomiCloseWaitSet(Entity *e) {
    e->action = 0xf;
    V(e)->unk_71 = data_020f26a8[V(e)->unk_71][Random() & 7];
    if (V(e)->unk_71 == 0xff) {
        V(e)->unk_71 = Random() & 1;
    }
    V(e)->unk_70 = data_020cf9b8[V(e)->unk_71];
}

ARM void getTsubomiMoveInfo(Entity *e) {
    V(e)->unk_74 = data_020d1464[Random() & 3];
    V(e)->unk_78 = *V(e)->unk_74++;
    V(e)->unk_7a = *V(e)->unk_74++;
    e->direction = *V(e)->unk_74++;
    V(e)->unk_7e = 0x80;
}

ARM int tblMove(Entity *e) {
    if (V(e)->unk_7e != 0) {
        V(e)->unk_7e--;
    }
    if (!(data_020d1450[V(e)->unk_7e >> 4] & data_0212c5bc)) {
        func_02086200(e, CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, (s16)V(e)->unk_78, (s16)V(e)->unk_7a));
    }
    MoveDir(e);
    GufuFuyusnd(e);
    if ((u16)(V(e)->unk_78 - e->x.HALF.HI + 2) <= 4 && (u16)(V(e)->unk_7a - e->y.HALF.HI + 2) <= 4) {
        if (*V(e)->unk_74 == 0xffff) {
            return 0;
        }
        V(e)->unk_78 = *V(e)->unk_74++;
        V(e)->unk_7a = *V(e)->unk_74++;
        e->direction = *V(e)->unk_74++;
        V(e)->unk_7e = 0x80;
        return 2;
    }
    return 1;
}
