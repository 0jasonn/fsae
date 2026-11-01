#ifndef WIP_G_SHARED_G_H
#define WIP_G_SHARED_G_H

#include "engine/entity.h"

// Used by the set object files; candidates for engine/functions.h.
void ScrPosSet(unsigned short x, unsigned short y); // original: ScrPosSet(unsigned short, unsigned short)

extern "C" {
void RewCellBack(unsigned short cell, unsigned short layer); // original name, no signature in the debug build
}

#endif
