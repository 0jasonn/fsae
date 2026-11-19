#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/set1st.h"

// set1st (0x02034124): makes four objects in a chain (three orbiting parts and the child they all point to), places
// the parts on a circle around the controller using the sine table, and registers them. Returns 0 when there are not
// enough free work objects.
int set1st(Entity *e) {
    Entity *partA;
    Entity *partB;
    Entity *partC;
    Entity *core;

    partA = GetObjWork();
    if (partA != NULL) {
        partB = GetObjWork2(partA);
        if (partB != NULL) {
            partC = GetObjWork2(partB);
            if (partC != NULL) {
                core = GetObjWork2(partC);
                if (core != NULL) {
                    partA->objKind = 3;
                    partB->objKind = 3;
                    partC->objKind = 3;
                    core->objKind = 3;
                    partA->objId = 0x2d;
                    partB->objId = 0x2d;
                    partC->objId = 0x2d;
                    core->objId = 0x2c;
                    core->type = 3;
                    partA->parent = e;
                    partB->parent = e;
                    partC->parent = e;
                    core->parent = e;
                    partA->child = core;
                    partB->child = core;
                    partC->child = core;
                    partA->direction = 0;
                    partB->direction = 0x55;
                    partC->direction = 0xab;
                    VARS(Vars_Set1stPart, partB)->partIndex = 1;
                    VARS(Vars_Set1stPart, partC)->partIndex = 2;
                    ObjPosCopyOfs32(e, partA, (s16)((trigTable[0] * 16) / 256) << 16,
                                    (s16)((-trigTable[0x40] * 16) / 256 - 4) << 16);
                    ObjPosCopyOfs32(e, partB, (s16)((trigTable[85] * 16) / 256) << 16,
                                    (s16)((-data_020d7f58[21] * 16) / 256 - 4) << 16);
                    ObjPosCopyOfs32(e, partC, (s16)((data_020d7f58[43] * 16) / 256) << 16,
                                    (s16)((-data_020d7f58[107] * 16) / 256 - 4) << 16);
                    ObjPosCopy(e, core);
                    RegistObjWork(4, partA);
                    RegistObjWork(4, partB);
                    RegistObjWork(4, partC);
                    RegistObjWork(5, core);
                    VARS(Vars_Set1stHead, e)->setState = 3;
                    VARS(Vars_Set1stHead, e)->setFlag = 0;
                    return 1;
                }
            }
        }
    }
    return 0;
}
