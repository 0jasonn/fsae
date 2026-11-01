#ifndef WIP_E_EM0E_UNITS_H
#define WIP_E_EM0E_UNITS_H

// Callees of the em0e units that are defined in another unit (original names from config/eur/original_names.tsv).
// Declared here so the em0e files compile; the reviewer moves them to engine/functions.h.
#include "engine/functions.h"

void hippariCheck(Entity *e); // original hippariCheck(OBJ_WORK_*), 0x0202d5bc (size 0x51c, not in this unit)
void darumaMgr(Entity *e); // original darumaMgr(OBJ_WORK_*), 0x0202e708 (size 0x1fc), defined in the em0f unit
extern "C" int func_02085294(Entity *e); // dsd name (thumb label), returns a state index

#endif
