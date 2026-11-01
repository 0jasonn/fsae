#ifndef WIP_C_C_DECLS_H
#define WIP_C_C_DECLS_H

// Declarations used by the implementer C units (src/wip/C/*.cpp) that are not in engine/functions.h yet.

#include "engine/functions.h"
#include "global.h"

// One record of the set table data_02117a88 (indexed by the chest kind, 4 bytes each): the arguments of
// GetSetWork and a halfword stored at +0x7e of the work it creates.
typedef struct TakaraSetEntry {
    u8 setKind; // first GetSetWork argument, 0x0b also sets the flag bytes of the player type
    u8 setArg1;
    u8 setArg2;
    u8 setParam; // stored as u16 at +0x7e of the new work
} TakaraSetEntry;

// Actor fields beyond the common part of Entity (only the offsets used by the C units are named)
typedef struct Vars_SetWork {
    u8 unk_00[0x7e];
    u16 setParam; // 7e, copied from TakaraSetEntry.setParam
} Vars_SetWork;

extern TakaraSetEntry data_02117a88[];
extern TakaraSetEntry data_02117aa0[];
extern TakaraSetEntry data_02117abc[];
extern Entity *data_0212c54c;
extern u8 data_0212cebc[];
extern u8 data_0212cee8[];
extern u8 data_0211682c[];
extern u8 data_0212ceca[];
extern u16 data_0212c58c[];
extern const u16 data_020dcba4[];
extern const s16 trigTable[];

void haneSet(Entity *e);
extern "C" void takaraAddEntry(Entity *e, u8 handlerIndex);
extern "C" void func_020841b0(Entity *e);
void zFree(void *p);
extern u8 data_0212cedc[];
extern u8 data_0212cecb[];
extern u8 data_0212ceb4[];
extern const s8 data_020dc70a[];
extern const s8 data_020dc77c[];
void tobashiInit(Entity *e);
extern "C" void AddHeart(Entity *e, s32 amount);
extern "C" void PlSoundReq(Entity *e, s32 sound);

#endif
