#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "actor/object/putobj.h"

// PutObjWork(e) (0x0204be88): releases an object. The object's group and owner bookkeeping is undone, the color
// slot of its init table row is released (PutObjColor, unless the row has bit 15 set), the object leaves the active
// list, its fields are cleared and its pool slot goes back on the free stack.
void PutObjWork(Entity *e) {
    PutObjOwner *owner;
    const u16 *row;
    const u16 *sub;
    u16 value;

    if (((PutObjNode *)e)->next == NULL) {
        return;
    }
    if (e->unk_53 != 0) {
        PutVGroup(e);
    }
    switch (e->objKind) {
    case 3:
        owner = (PutObjOwner *)e->linkedEntity;
        if (owner != NULL) {
            owner->childCount -= 1;
            if (*((u8 *)e + 0x68) != 0) {
                owner = (PutObjOwner *)e->linkedEntity;
                owner->childFlags &= (u16)~flagBits[(*((u8 *)e + 0x68) - 1) & 0x1f];
            }
        }
        row = enemyInitTable + e->objId * 8;
        if (row[0] == 0xffff) {
            sub = enemyInitIndirect[row[1]];
            value = ((const u16 *)((const u8 *)sub + e->type * 0x10))[1];
            if (!(value & 0x8000)) {
                PutObjColor(value);
            }
        } else {
            if (!(row[1] & 0x8000)) {
                PutObjColor(row[1]);
            }
        }
        break;
    case 6:
        row = setInitTable + e->objId * 3;
        if (row[0] == 0xffff) {
            sub = setInitSubTables[row[1]];
            sub = sub + e->type * 3;
            value = sub[1];
            if (!(value & 0x8000)) {
                PutObjColor(value);
            }
        } else {
            if (row[0] == 0xfffe) {
                break;
            }
            if (!(row[1] & 0x8000)) {
                PutObjColor(row[1]);
            }
        }
        break;
    case 4:
        row = data_020dd0d0 + e->objId * 8;
        if (row[0] == 0xffff) {
            sub = data_020dd068[row[1]];
            value = ((const u16 *)((const u8 *)sub + e->type * 0x10))[1];
            if (!(value & 0x8000)) {
                PutObjColor(value);
            }
        } else {
            if (!(row[1] & 0x8000)) {
                PutObjColor(row[1]);
            }
        }
        break;
    }
    ((PutObjNode *)e)->prev->next = ((PutObjNode *)e)->next;
    ((PutObjNode *)e)->next->prev = ((PutObjNode *)e)->prev;
    if (e == (Entity *)data_0212c52c) {
        data_0212c52c = ((PutObjNode *)e)->prev;
    }
    e->spriteSettings.b0 = 0;
    e->statusFlags = 0;
    e->contactFlags = 0;
    e->unk_42 = 0;
    e->health = 0;
    ((PutObjNode *)e)->next = NULL;
    data_02134dd0[data_021348d4++] = (u32)((u8 *)e - data_0212f890) >> 7;
    if ((u8 *)e < data_02134290) {
        data_0212c4f4 -= 1;
    } else {
        data_0212c4cc -= 1;
    }
}
