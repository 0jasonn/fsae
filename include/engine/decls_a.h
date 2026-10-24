#ifndef WIP_A_DECLS_A_H
#define WIP_A_DECLS_A_H

// Callees used by the implementer A files (src/wip/A/) that engine/functions.h does not declare yet.
// Unmangled originals are extern "C"; the reviewer moves the rest into functions.h.
#include "engine/functions.h"

extern "C" void MI_UncompressLZ8(const void *src, void *dst);
extern "C" void MI_UncompressLZ16(const void *src, void *dst);
extern "C" void MIi_CpuCopy16(const void *src, void *dst, u32 size);

// KnifeApp::getZelmapResource(unsigned long) (plain name in symbols.txt). The first argument is the KnifeApp instance.
extern "C" u32 KnifeApp_getZelmapResource(void *app, u32 id);

// Block helpers of the bganm module (src/game/bganm.cpp, C++ linkage).
BOOL Check1BlockOshiYoyaku(u16 a, u16 b);
void Set1BlockOshiYoyaku(u16 a, u16 b);

// Shared map and player-block data used by the front check code.
extern const s16 cellDeltaTable[]; // cell offsets indexed by mode >> 3
extern u8 data_0212cee6[];         // u16 flags, stride 0x94 per player block

// Boots module (src/object/boots.cpp, src/wip/A/boots_2.cpp).
void zFree(void *p);                       // original zFree(void*)
void boots_plsync(Entity *e, Entity *tmpl); // original plsync(OBJ_WORK_*, OBJ_WORK_*)
extern "C" void func_0208a224(Entity *e, u32 a, s32 x, s32 y); // thumb, 0x0208a224
extern u8 data_0212ced8[];                 // template pointer per type (stride 0x94)
extern u8 data_0212cece[];                 // flag byte per template entry (stride 0x94)
extern u8 data_0212cedc[];                 // second pointer per template entry: boots object in use
extern const s8 data_020ce52c[];           // hitbox offsets, four bytes per pair of animation states
extern const s8 data_020ce51c[];           // (x, y) offsets per animation state, pairs of signed bytes

#endif
