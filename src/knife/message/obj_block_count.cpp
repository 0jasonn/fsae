#include "knife/message/rendertarget_api.h"

extern "C" s32 func_020c61f4(s32 width, s32 height) {
    u32 columns = (u32)width;
    u32 rows = (u32)height;
    u32 fullColumns = columns >> 3;
    u32 fullRows = rows >> 3;
    u32 narrowColumns = ((columns & 2) >> 1) + (columns & 1);
    u32 fourCellColumn = (columns & 4) >> 2;
    u32 shortRows = ((rows & 2) >> 1) + (rows & 1);
    u32 fourCellRow = (rows & 4) >> 2;

    u32 count = 0;
    count += fullColumns * fullRows;
    count += fullRows * ((narrowColumns << 1) + fourCellColumn);
    count += fullColumns * ((shortRows << 1) + fourCellRow);
    count += (narrowColumns + fourCellColumn) * (shortRows + fourCellRow);
    return (s32)count;
}

