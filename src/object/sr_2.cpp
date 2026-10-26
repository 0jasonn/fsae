#include "engine/functions.h"
#include "engine/misc_d.h"
#include "global.h"

// Rupee rush (module sr): setupRupeeRush places the rupee rush object (kind 3, id 9) on a free cell of the
// board. Dice index and cell tables are read by getRupeeRushDiceIndex (0x02077650, parked).
extern "C" u32 getNumberOfObj(u8 kind, u8 id);
extern "C" u8 getRupeeRushDiceIndex(void);
extern u8 rupeeRushState[];        // rupeeRushState: [0] rush step counter, [1] index into rupeeRushSetId
extern const u8 rupeeRushSetId[];  // rupeeRushSetId: set id per index
extern const u8 rupeeRushCell[];   // rupeeRushCell: (x, y) cell pairs
extern EntityNode data_0212c6d0;   // end sentinel of the object list (the head itself is data_0212c6b0[4])

// setupRupeeRush (0x02077684)
extern "C" void setupRupeeRush(int reuseEnemy);
ARM void setupRupeeRush(int reuseEnemy) {
    Entity *obj;
    Entity *cur;
    u8 cell;
    u8 found;

    if (reuseEnemy != 0 && getNumberOfObj(3, 9) <= data_0212c7c8.unk_0 * 2 + 1) {
        obj = GetEnemyWork(9);
        if (obj != 0) {
            obj->type = rupeeRushState[1];
        }
    } else {
        obj = GetSetWork(0, rupeeRushSetId[rupeeRushState[1]], 0);
    }
    if (obj == 0) {
        return;
    }
    if (obj->objKind == 3 && obj->objId == 9) {
        do {
            found = 0;
            cell = getRupeeRushDiceIndex();
            obj->x.HALF.HI = (rupeeRushCell[cell * 2] << 4) + 7;
            obj->y.HALF.HI = (rupeeRushCell[cell * 2 + 1] << 4) + 7;
            cur = (Entity *)data_0212c6b0[4].next;
            while (cur != (Entity *)&data_0212c6d0) {
                if (cur != obj && cur->objKind == 3 && cur->objId == 9 && cur->x.HALF.HI == obj->x.HALF.HI &&
                    cur->y.HALF.HI == obj->y.HALF.HI) {
                    found = 1;
                    break;
                }
                cur = (Entity *)((EntityNode *)cur)->next;
            }
        } while (found != 0);
    } else {
        cell = getRupeeRushDiceIndex();
        obj->x.HALF.HI = (rupeeRushCell[cell * 2] << 4) + 8;
        obj->y.HALF.HI = (rupeeRushCell[cell * 2 + 1] << 4) + 8;
    }
    obj->direction = 0xff;
    obj->layer = 0x4000;
    KemuriSet(obj);
}
