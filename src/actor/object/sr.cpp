#include "engine/functions.h"
#include "engine/misc.h"
#include "global.h"
#include "actor/object/sr_api.h"
#include "engine/display_state.h"

// Rupee rush (module sr): setupRupeeRush places the rupee rush object (kind 3, id 9) on a free cell of the
// board. Dice index and cell tables are read by getRupeeRushDiceIndex (0x02077650, parked).
extern "C" u32 getNumberOfObj(u8 kind, u8 id);
u8 getRupeeRushDiceIndex(void); // 0x02077650, rupeerush_dice.cpp
extern u8 rupeeRushState[];        // rupeeRushState: [0] rush step counter, [1] index into rupeeRushSetId
extern const u8 rupeeRushSetId[];  // rupeeRushSetId: set id per index
extern const u8 rupeeRushCell[];   // rupeeRushCell: (x, y) cell pairs

// setupRupeeRush (0x02077684)
void setupRupeeRush(int reuseEnemy) {
    Entity *obj;
    Entity *cur;
    u8 cell;
    u8 found;

    if (reuseEnemy != 0 && getNumberOfObj(3, 9) <= gameState.playerCount * 2 + 1) {
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
            while (cur != (Entity *)&data_0212c6b0[4]) {
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

// Staffroll step machine (module sr): StaffrollTask runs the step at data_0212c500 of srStepTable, sr_wait waits for the
// communication to report that the step is complete. data_0212c4dc is the phase inside the wait.
//   StaffrollTask (0x02077810), sr_wait (0x0207790c).

extern u8 data_0212c4dc;             // phase of sr_wait: 0 requests, 1 waits for the state code, then the step advances
extern u8 data_0212c500;             // step index into srStepTable
extern void (*srStepTable[])(void); // srStepTable: sr_init, sr_wait, sr_makemap, sr_start, sr_main, ...
extern u32 data_0212c550;
extern u32 data_0212c554;

extern "C" s32 WXC_GetStateCode(void);
void ComRequest(u8 request); // C++ name _Z10ComRequesth

// StaffrollTask (0x02077810)
void StaffrollTask(void) {
    srStepTable[data_0212c500]();
}
