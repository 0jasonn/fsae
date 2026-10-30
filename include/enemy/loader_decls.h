#ifndef WIP_B_LOADER_DECLS_H
#define WIP_B_LOADER_DECLS_H

// Declarations for the demo and staff roll loaders (YouseiDemoLoad, StaffrollLoad) of implementer B.
// Linkage follows the symbol names in config/eur/arm9/symbols.txt: plain names are extern "C", mangled ones are C++.

#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

// FRAME_INFO_ (original name): one frame record, read by MPlayerSet, FrameSet and MultiRoomInit
typedef struct FRAME_INFO_ {
    /* 00 */ u8 frameNo;
    /* 01 */ u8 roomNo;
    /* 02 */ u8 unk_02[0x12];
    /* 14 */ const u32 *infoRows;
} FRAME_INFO_;

extern "C" void FrameSet(u16 frameNo);                    // original FrameSet(unsigned short), 0x0205715c
extern "C" void MultiRoomInit(u16 roomNo);                // original MultiRoomInit(unsigned short), 0x02056f4c
extern "C" void MPlayerSet(FRAME_INFO_ *frame);           // original MPlayerSet(FRAME_INFO_*), 0x0204c950
void MultiEventSet(u16 *list, u8 a, u8 b, u8 c);          // original MultiEventSet(unsigned short*, unsigned char x3), 0x0204602c
void MultiRoomSet(void);                                  // original MultiRoomSet(), 0x020572b4
void func_0208309c(void);                                 // thumb helper, mangled _Z13func_0208309cv

extern FRAME_INFO_ staffrollFrameInfo;                   // ROM frame record used by StaffrollLoad (staffrollFrameInfo)
extern FRAME_INFO_ *youseiFrameTable[];                  // frame record table indexed by data_0212c7c8.unk_1[0] (youseiFrameTable)
extern const u32 *data_02134968[];                        // info table, one row pointer per area (see src/engine/info.cpp)
extern u8 data_0212c4c8;
extern u8 data_021348f4[];

#endif
