#ifndef WIP_B_DECLS_B2_H
#define WIP_B_DECLS_B2_H

#include "engine/entity.h"

// Declarations used by the wip/B files that include/engine/functions.h does not have yet.

// dispctrl.cpp (module disp), C++ linkage
void DispCtrlClear(void);

// comm module (src/game/comm*.cpp, dsd names below are the original mangled names)
int CommFrameSync(void);
void CommUpdateJoy(void);
void CommFrameUpdate(void);
extern "C" void keyClear(void);

// doorsel_appear callee (original GetTablePlNum(short*, unsigned char), mangled _Z13GetTablePlNumPsh)
s16 *GetTablePlNum(s16 *table, u8 index);

// display and DMA state (names from symbols.txt)
extern u8 data_0212c4e0;
extern u8 data_0212c4c8;
extern u8 data_0212c4dc;   // doorsel sub-step
extern u8 data_0212c500;   // doorsel step
extern u32 data_0212c56c;
extern u32 data_0212c570;
extern u32 data_0212c528;
extern u8 data_0212c594[];
extern u8 data_021349c0[];   // ResultState block (enemy/ending.h), u16 timer at 4
extern u8 data_0212c75c[];   // DisplayShadow (enemy/ending.h), u16 at 0x18
extern u16 data_0212c58c[];
extern s16 data_020f260c[];   // pairs of s16 positions for the door select sprites
extern u8 data_0212ccb0[];
extern u8 data_0212cdb0[];
extern u8 data_0212de50[];
extern u8 data_021361a0[];
extern u8 objAffineSet[];
extern u8 hblankDma;
extern u8 data_0212c7c8[];   // game state, byte 0x8e is the game state
extern u8 data_0212ceb0[];   // PlayerData array, stride 0x94


// em28 module callees (src/enemy/em28_3.cpp, em28_4.cpp, em1c and em26 headers hold the other declarations)
Entity *plCheck(Entity *e);
void dushInit(Entity *e, Entity *target);
void swordMgr(Entity *e);
u8 EmMagneMove(Entity *e, u16 speed);
extern const EntityFunc data_020d334c[]; // per action function table of em28

// TwlSDK and resid helpers (extern "C", plain names in symbols.txt)
extern "C" u16 GetResTranslateID(u16 id, const void *table, s32 count); // resid.cpp
extern "C" void MIi_CpuCopy16(const void *src, void *dst, u32 size);
extern "C" void MI_UncompressLZ16(const void *src, void *dst, u32 flags); // flags: the entry word, bit 31 set

// srchcells.cpp callees (plain names in symbols.txt)
extern "C" void *zMalloc(u16 size);
extern "C" void shuffledata(u16 *list, u16 count);

#endif
