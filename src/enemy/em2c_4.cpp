#include "engine/functions.h"
#include "enemy/em2c.h"
#include "global.h"

ARM BOOL set3rd(Entity *e) {
    Entity *partA;
    Entity *partB;
    Entity *partC;
    Entity *partD;
    if ((partA = GetObjWork()) != NULL && (partB = GetObjWork2(partA)) != NULL && (partC = GetObjWork2(partB)) != NULL &&
        (partD = GetObjWork2(partC)) != NULL) {
        partA->unk_08 = 3;
        partB->unk_08 = 3;
        partC->unk_08 = 3;
        partD->unk_08 = 3;
        partA->unk_09 = 0x2c;
        partB->unk_09 = 0x2c;
        partC->unk_09 = 0x2d;
        partD->unk_09 = 0x2c;
        partA->type = 1;
        partB->type = 1;
        partD->type = 3;
        partC->type2 = 2;
        partD->type2 = 2;
        partA->parent = e;
        partB->parent = e;
        partC->parent = e;
        partD->parent = e;
        partA->child = partD;
        partB->child = partD;
        partC->child = partD;
        V(partA)->side = 0;
        V(partB)->side = 1;
        V(partA)->lockBit = 0x80;
        V(partB)->lockBit = 0x40;
        V(partA)->lockEntity = partC;
        V(partB)->lockEntity = partC;
        ObjPosCopy(e, partA);
        ObjPosCopy(e, partB);
        ObjPosCopy(e, partC);
        ObjPosCopy(e, partD);
        RegistObjWork(4, partA);
        RegistObjWork(4, partB);
        RegistObjWork(4, partC);
        RegistObjWork(5, partD);
        partC->direction = 0x20;
        VCT(e)->chainStep = 0;
        VCT(e)->chainBuilt = 1;
        return TRUE;
    }
    return FALSE;
}

