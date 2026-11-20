#ifndef GAME_STOPBLOCK_4_H
#define GAME_STOPBLOCK_4_H

#include "types.h"
#include "game/stopblock.h"  // STOPBLOCK_WORK_ and sbRegistSub (C++ linkage, as in the original)


// Stop block tables: data_02134f30..data_02134ff0 (first pass), data_02134ff0..+0x30 records (second pass); 0x30 records each
extern STOPBLOCK_WORK_ data_02134f30[];
extern STOPBLOCK_WORK_ data_02134ff0[];

extern "C" {
int func_0208af18(u16 value); // thumb, unmangled (0x0208af18); returns non-zero for a key it accepts
void RewCellBack(u16 cell, u16 flag);
}
void sbKemuriSet(STOPBLOCK_WORK_ *block);           // _Z11sbKemuriSetP15STOPBLOCK_WORK_
void set5c_changeiroankyo(u16 cell, u16 value);     // _Z20set5c_changeiroankyott

// sbGarbageCollection has C++ linkage (original sbGarbageCollection(STOPBLOCK_WORK_*, STOPBLOCK_WORK_*)), 0x0204ec38.
void sbGarbageCollection(STOPBLOCK_WORK_ *begin, STOPBLOCK_WORK_ *end);

#endif
