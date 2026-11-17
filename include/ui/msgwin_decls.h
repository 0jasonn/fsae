#ifndef WIP_MSGWIN_DECLS_H
#define WIP_MSGWIN_DECLS_H

#include "engine/functions.h"
#include "ui/message.h"
#include "ui/msgwin.h"

extern u8 data_0216f001[];  // telopWindowSlots[i].active (stride 8)
extern s8 data_0216f007[];  // telopWindowSlots[i].height (stride 8), the telop line mode

// The telop slot copy in telopWindow is a two-word struct copy (the original slot type has 4-byte alignment, WindowSlot
// has 1 and would be copied byte by byte). Proposal: give WindowSlot 4-byte alignment instead of this view.
typedef struct SlotWords {
    u32 low;
    u32 high;
} SlotWords;

// Declared here for the reviewer to move into engine/functions.h (original CockpitRecovery(unsigned char, unsigned char)).
void CockpitRecovery(u8 kind, u8 amount);

#endif
