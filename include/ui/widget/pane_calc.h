#ifndef WIP_F_PANE_CALC_H
#define WIP_F_PANE_CALC_H

// Parameters of the scaled rectangle helpers (Pane_calcScaledX and Pane_calcScaledY).
// The record is read as bytes: base[k] at +0, span[k] at +2, and the index at +4.

#include "types.h"

typedef struct PaneScaleParam {
    s8 base[2];   // 0x00: base value of each of the two axis entries
    s8 span[2];   // 0x02: span value of each entry
    u8 index;     // 0x04: the entry written first (0 or 1, any nonzero value counts as 1)
} PaneScaleParam;

#endif
