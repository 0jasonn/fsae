#include "engine/functions.h"
#include "global.h"
#include "ui/groupselectuiview.h"
#include "ui/groupselectuiview_api.h"

// Functions in this file (original names from the debug build):
//   linkPalToPanePal (0x020b11dc)

// linkPalToPanePal(signed char) (0x020b11dc): entry of the palette link table
s8 linkPalToPanePal(s8 index) {
    LinkPalTable table;

    table = data_020ded44;
    return table.entry[index];
}
