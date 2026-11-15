#include "engine/functions.h"
#include "global.h"
#include "actor/object/set6b_rewdoor.h"

// Rewrites the map cells under a door block (set6b_rewDoor, 0x020623c8). Same scheme as rewHalf; bit 2 of the type
// selects the second set of cell lists and type & 7 the cells around the block.
void set6b_rewDoor(Entity *e) {
    const u16 *list;
    int cell;
    const u8 *bgmRow;

    if (gameState.unk_01 == 6) {
        bgmRow = bgmIndexTable[gameState.unk_01][gameState.unk_48].table;
        if (e->type2 & 4) {
            list = rewDoorListsBgmB[bgmRow[1]] + (VS(e)->listSet * 0x18 + (e->type2 & 3) * 6);
        } else {
            list = rewDoorListsBgmA[bgmRow[1]] + (VS(e)->listSet * 0x18 + (e->type2 & 3) * 6);
        }
    } else {
        if (e->type2 & 4) {
            list = rewDoorListsPickB[gameState.unk_01] + (VS(e)->listSet * 0x18 + (e->type2 & 3) * 6);
        } else {
            list = rewDoorListsPickA[gameState.unk_01] + (VS(e)->listSet * 0x18 + (e->type2 & 3) * 6);
        }
    }
    cell = VS(e)->cellA;
    switch (e->type2 & 7) {
    case 0:
        RewCell(list[0], cell - 65, 0x8000);
        RewCell(list[1], cell - 64, 0x8000);
        RewCell(list[2], cell - 63, 0x8000);
        RewCell(list[3], cell - 1, 0x4000);
        RewCell(list[4], cell, 0x4000);
        RewCell(list[5], cell + 1, 0x4000);
        cell = VS(e)->cellB;
        if (cell != 0xffff) {
            RewCell(list[12], cell - 1, 0x4000);
            RewCell(list[13], cell, 0x4000);
            RewCell(list[14], cell + 1, 0x4000);
            RewCell(list[15], cell + 63, 0x8000);
            RewCell(list[16], cell + 64, 0x8000);
            RewCell(list[17], cell + 65, 0x8000);
        }
        break;
    case 1:
        RewCell(list[0], cell - 64, 0x4000);
        RewCell(list[1], cell - 63, 0x8000);
        RewCell(list[2], cell, 0x4000);
        RewCell(list[3], cell + 1, 0x8000);
        RewCell(list[4], cell + 64, 0x4000);
        RewCell(list[5], cell + 65, 0x8000);
        cell = VS(e)->cellB;
        if (cell != 0xffff) {
            RewCell(list[12], cell - 65, 0x8000);
            RewCell(list[13], cell - 64, 0x4000);
            RewCell(list[14], cell - 1, 0x8000);
            RewCell(list[15], cell, 0x4000);
            RewCell(list[16], cell + 63, 0x8000);
            RewCell(list[17], cell + 64, 0x4000);
        }
        break;
    case 2:
        RewCell(list[0], cell - 1, 0x4000);
        RewCell(list[1], cell, 0x4000);
        RewCell(list[2], cell + 1, 0x4000);
        RewCell(list[3], cell + 63, 0x8000);
        RewCell(list[4], cell + 64, 0x8000);
        RewCell(list[5], cell + 65, 0x8000);
        cell = VS(e)->cellB;
        if (cell != 0xffff) {
            RewCell(list[-12], cell - 65, 0x8000);
            RewCell(list[-11], cell - 64, 0x8000);
            RewCell(list[-10], cell - 63, 0x8000);
            RewCell(list[-9], cell - 1, 0x4000);
            RewCell(list[-8], cell, 0x4000);
            RewCell(list[-7], cell + 1, 0x4000);
        }
        break;
    case 3:
        RewCell(list[0], cell - 65, 0x8000);
        RewCell(list[1], cell - 64, 0x4000);
        RewCell(list[2], cell - 1, 0x8000);
        RewCell(list[3], cell, 0x4000);
        RewCell(list[4], cell + 63, 0x8000);
        RewCell(list[5], cell + 64, 0x4000);
        cell = VS(e)->cellB;
        if (cell != 0xffff) {
            RewCell(list[-12], cell - 64, 0x4000);
            RewCell(list[-11], cell - 63, 0x8000);
            RewCell(list[-10], cell, 0x4000);
            RewCell(list[-9], cell + 1, 0x8000);
            RewCell(list[-8], cell + 64, 0x4000);
            RewCell(list[-7], cell + 65, 0x8000);
        }
        break;
    case 4:
        RewCell(list[0], cell - 65, 0x8000);
        RewCell(list[1], cell - 64, 0x8000);
        RewCell(list[2], cell - 63, 0x8000);
        RewCell(list[3], cell - 1, 0x4000);
        RewCell(list[4], cell, 0x4000);
        RewCell(list[5], cell + 1, 0x4000);
        break;
    case 5:
        RewCell(list[0], cell - 64, 0x4000);
        RewCell(list[1], cell - 63, 0x8000);
        RewCell(list[2], cell, 0x4000);
        RewCell(list[3], cell + 1, 0x8000);
        RewCell(list[4], cell + 64, 0x4000);
        RewCell(list[5], cell + 65, 0x8000);
        break;
    case 6:
        RewCell(list[0], cell - 1, 0x4000);
        RewCell(list[1], cell, 0x4000);
        RewCell(list[2], cell + 1, 0x4000);
        RewCell(list[3], cell + 63, 0x8000);
        RewCell(list[4], cell + 64, 0x8000);
        RewCell(list[5], cell + 65, 0x8000);
        break;
    case 7:
        RewCell(list[0], cell - 65, 0x8000);
        RewCell(list[1], cell - 64, 0x4000);
        RewCell(list[2], cell - 1, 0x8000);
        RewCell(list[3], cell, 0x4000);
        RewCell(list[4], cell + 63, 0x8000);
        RewCell(list[5], cell + 64, 0x4000);
        break;
    }
}
