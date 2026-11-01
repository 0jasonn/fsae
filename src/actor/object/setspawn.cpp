#include "engine/functions.h"
#include "engine/player.h"
#include "actor/object/setspawn.h"

// Rolls a child from the spawn tables of the parent. 0x0207c408.
void Set_TrySpawnChild(Entity *parent, u8 tableIndex, Entity *target) {
    u8 kind;
    u8 typeIndex;
    u8 roll;
    const u8 *record;
    Entity *child;

    if (data_0212c4f4 > 0x70) {
        return;
    }
    if (func_02083d28(parent) != 0) {
        return;
    }
    if (target == NULL) {
        return;
    }
    if ((Random() & 0xff) >= Set_SpawnChanceTable[tableIndex]) {
        return;
    }
    if (AssignObj(target) != 0 && target->objKind != 3 && target->type <= 3) {
        typeIndex = data_0212c81c[target->type];
    } else {
        typeIndex = 5;
    }
    roll = Random() & 0x1f;
    kind = Set_KindTables[tableIndex][data_0212c7c8.unk_01][typeIndex][roll];
    record = &Set_KindRecords[kind * 4];

    switch (kind) {
    case 0x0e:
        child = GetObjWork();
        if (child == NULL) {
            return;
        }
        child->objKind = 8;
        child->objId = 4;
        child->type = 0xff;
        ObjPosCopy(parent, child);
        child->x.HALF.HI = parent->x.HALF.HI;
        child->y.HALF.HI = parent->y.HALF.HI;
        child->unk_5e.b0 = 0;
        RegistObjWork(2, child);
        return;
    case 0x11:
        if (Set_Kind11Threshold[data_0212c7c8.unk_01] >= (Random() & 0x1f)) {
            record = Set_Record11Hit;
        } else {
            record = Set_Record11Miss;
        }
        break;
    case 0x12:
        if (Set_Kind12Threshold[data_0212c7c8.unk_49[4]] >= (Random() & 0x1f)) {
            record = Set_Record12Hit;
        } else {
            record = Set_Record12Miss;
        }
        break;
    }

    child = GetSetWork(record[0], record[1], record[2]);
    if (child == NULL) {
        return;
    }
    child->x.HALF.HI = parent->x.HALF.HI;
    child->y.HALF.HI = parent->y.HALF.HI;
    child->layer = parent->layer & ~0x3000;
    func_0208ae78(child);
}
