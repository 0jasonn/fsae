#include "engine/functions.h"
#include "game/srchcells_api.h"
#include "game/randomset.h"

// GetCellsInRandomSet (0x0204e49c): returns the random set record for (cell, w, h). A record that matches is reused;
// otherwise srchCells makes a block and it is stored in a free record. NULL when nothing can be made.
void *GetCellsInRandomSet(u16 cell, u16 w, u16 h) {
    u16 i;
    u16 j;
    u16 *cells;

    for (i = 0; i < 8; i++) {
        if (cell == data_02134ae8[i].cell && w == data_02134ae8[i].width && h == data_02134ae8[i].height) {
            return &data_02134ae8[i];
        }
    }
    cells = srchCells(cell, w, h);
    if (cells == NULL) {
        return NULL;
    }
    for (j = 0; j < 8; j++) {
        if (data_02134ae8[j].cells == NULL) {
            data_02134ae8[j].cells = cells;
            data_02134ae8[j].cell = cell;
            data_02134ae8[j].width = w;
            data_02134ae8[j].height = h;
            data_02134ae8[j].unk_08 = 0;
            return &data_02134ae8[j];
        }
    }
    zFree(cells);
    return NULL;
}
