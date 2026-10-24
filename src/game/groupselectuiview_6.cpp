#include "engine/functions.h"
#include "global.h"
#include "game/groupselectuiview.h"

// Functions in this file (original names from the debug build):
//   linkPalToPanePal (0x020b11dc)

// linkPalToPanePal(signed char) (0x020b11dc): entry of the palette link table
extern "C" s8 linkPalToPanePal(s8 index);
ARM s8 linkPalToPanePal(s8 index) {
    LinkPalTable table;

    table = data_020ded44;
    return table.entry[index];
}
