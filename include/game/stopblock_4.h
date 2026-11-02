#ifndef WIP_B_STOPBLOCK_4_H
#define WIP_B_STOPBLOCK_4_H

#include "types.h"

// Same layout as STOPBLOCK_WORK_ in game/stopblock.h. That header cannot be included here: it declares sbRegistSub
// with C++ linkage, and the ROM symbol is plain (extern "C"). Merge the two once that prototype is moved.
typedef struct STOPBLOCK_WORK_ {
    /* 00 */ u16 key;
    /* 02 */ u8 state;
    /* 03 */ u8 unk_03;
} STOPBLOCK_WORK_;

// Stop block tables: data_02134f30..data_02134ff0 (first pass), data_02134ff0..data_021350b0 (second pass)
extern STOPBLOCK_WORK_ data_02134f30[];
extern STOPBLOCK_WORK_ data_02134ff0[];
extern STOPBLOCK_WORK_ data_021350b0[];

extern "C" {
int sbRegistSub(u16 *key, u8 kind, STOPBLOCK_WORK_ *begin, STOPBLOCK_WORK_ *end); // 0x0204e7d4
int func_0208af18(u16 value); // thumb, unmangled (0x0208af18); returns non-zero for a key it accepts
void RewCellBack(u16 cell, u16 flag);
void sbGarbageCollection(STOPBLOCK_WORK_ *begin, STOPBLOCK_WORK_ *end);
}
void RewCellOne(u16 id, u16 cell, u16 flag);       // _Z10RewCellOnettt
void sbKemuriSet(STOPBLOCK_WORK_ *block);           // _Z11sbKemuriSetP15STOPBLOCK_WORK_
void set5c_changeiroankyo(u16 cell, u16 value);     // _Z20set5c_changeiroankyott

#endif
