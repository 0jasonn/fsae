#ifndef UI_FILE_SELECTION_BUFFERS_H
#define UI_FILE_SELECTION_BUFFERS_H

#include "types.h"

typedef u16 FileSelectionTilemap[32][32];

struct FileSelectionBuffers {
    FileSelectionTilemap *bg1;
    FileSelectionTilemap *bg2;
    u8 *cells;
};

extern "C" FileSelectionBuffers data_02180d9c;

#endif
