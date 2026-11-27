#include "engine/functions.h"
#include "engine/map_state.h"
#include "game/multiplay.h"
#include "game/autoset.h"

// AutoSet(), 0x02023940: walks every cell of the room (rows of 0x40 cells). For each cell it looks the first-layer
// kind up in data_020cd744 and, if nothing matched there, the second-layer kind in data_020cd798; a match spawns the
// listed object at the cell centre on the current layer (mapState.unk_12) and registers it in its work list.
void AutoSet(void) {
    const AutoSetEntry *entry;
    u16 cell;
    u16 rows;
    BOOL found;
    Entity *obj;
    u16 y;
    u16 x;
    u16 cols;

    cell = 0;
    cols = mapState.limitX >> 4;
    rows = mapState.limitY >> 4;

    for (y = 0; y < rows; y++) {
        for (x = 0; x < cols; x++, cell++) {
            found = FALSE;
            entry = data_020cd744;
            do {
                if (entry->cellKind == GetCellKind(cell, 0x8000)) {
                    obj = GetObjWork();
                    if (obj != NULL) {
                        obj->objKind = entry->objKind;
                        obj->objId = entry->objId;
                        obj->type = entry->typeWord;
                        obj->type2 = entry->typeWord >> 8;
                        obj->x.HALF.HI = ((cell & 0x3f) << 4) + 8;
                        obj->y.HALF.HI = ((cell & 0xfc0) >> 2) + 8;
                        obj->layer = mapState.unk_12 | 0x8000;
                        RegistObjWork(data_020d7c60[entry->objKind & 0xff], obj);
                    }
                    found = TRUE;
                    break;
                }
                entry++;
            } while (entry->cellKind != 0xffff);
            if (!found) {
                entry = data_020cd798;
                do {
                    if (entry->cellKind == GetCellKind(cell, 0x4000)) {
                        obj = GetObjWork();
                        if (obj != NULL) {
                            obj->objKind = entry->objKind;
                            obj->objId = entry->objId;
                            obj->type = entry->typeWord;
                            obj->type2 = entry->typeWord >> 8;
                            obj->x.HALF.HI = ((cell & 0x3f) << 4) + 8;
                            obj->y.HALF.HI = ((cell & 0xfc0) >> 2) + 8;
                            obj->layer = mapState.unk_12 | 0x4000;
                            RegistObjWork(data_020d7c60[entry->objKind & 0xff], obj);
                        }
                        break;
                    }
                    entry++;
                } while (entry->cellKind != 0xffff);
            }
        }
        cell += 0x40 - cols;
    }
}
