#include "engine/functions.h"
#include "enemy/em2f.h"
#include "global.h"

ARM BOOL setTsubomi(Entity *e) {
    Entity *first;
    Entity *second;
    if ((first = GetObjWork()) != NULL && (second = GetObjWork2(first)) != NULL) {
        first->objKind = 3;
        second->objKind = 3;
        first->objId = 0x30;
        second->objId = 0x30;
        first->type2 = 0;
        second->type2 = 1;
        first->direction = 0xa0;
        second->direction = 0x60;
        first->parent = e;
        second->parent = e;
        first->child = second;
        second->child = first;
        ObjPosCopy(e, first);
        ObjPosCopy(e, second);
        RegistObjWork(4, first);
        RegistObjWork(4, second);
        return TRUE;
    }
    return FALSE;
}

ARM void tsubomiCloseWaitSet(Entity *e) {
    e->action = 0xf;
    V(e)->tsubomiSlot = em2f_slotNext[V(e)->tsubomiSlot][Random() & 7];
    if (V(e)->tsubomiSlot == 0xff) {
        V(e)->tsubomiSlot = Random() & 1;
    }
    V(e)->subPhase = flagBits[V(e)->tsubomiSlot];
}

ARM void getTsubomiMoveInfo(Entity *e) {
    V(e)->pathCursor = em2f_tsubomiPaths[Random() & 3];
    V(e)->targetX = *V(e)->pathCursor++;
    V(e)->targetY = *V(e)->pathCursor++;
    e->direction = *V(e)->pathCursor++;
    V(e)->pathWait = 0x80;
}

ARM int tblMove(Entity *e) {
    if (V(e)->pathWait != 0) {
        V(e)->pathWait--;
    }
    if (!(em2f_moveGateMasks[V(e)->pathWait >> 4] & data_0212c5bc)) {
        func_02086200(e, CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, (s16)V(e)->targetX, (s16)V(e)->targetY));
    }
    MoveDir(e);
    GufuFuyusnd(e);
    if ((u16)(V(e)->targetX - e->x.HALF.HI + 2) <= 4 && (u16)(V(e)->targetY - e->y.HALF.HI + 2) <= 4) {
        if (*V(e)->pathCursor == 0xffff) {
            return 0;
        }
        V(e)->targetX = *V(e)->pathCursor++;
        V(e)->targetY = *V(e)->pathCursor++;
        e->direction = *V(e)->pathCursor++;
        V(e)->pathWait = 0x80;
        return 2;
    }
    return 1;
}
