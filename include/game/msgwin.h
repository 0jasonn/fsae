#ifndef WIP_C_MSGWIN_H
#define WIP_C_MSGWIN_H

#include "types.h"

// Message window drawing (0x0204ad38..0x0204b250). Declared here until the reviewer moves them into engine/functions.h.
void MessageFrameDisp(u16 *tiles, s16 width, s16 height, u16 attr);
void MessageFrameClear(u16 *tiles, s16 width, s16 height, u16 attr);
void dispString(void);
void dispEnqCursor(void);
void dispCursor(void);

#endif
