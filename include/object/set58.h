#ifndef WIP_D_SET58_H
#define WIP_D_SET58_H

// Set58 actor (body, hane, hamon, youseidama, aura, milkcrown, sazanami, hikari, tamahikari, kougyoku, fairy) fields and data

#include "engine/entity.h"

typedef struct Vars_Set58 {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u16 unk_7c;
} Vars_Set58;
#define V58(e) VARS(Vars_Set58, e)

extern const EntityFunc set58_typeActions[]; // set58_typeActions, indexed by e->type
extern const EntityFunc set58_bodyActions[]; // set58_bodyActions, indexed by e->action
extern u8 set58_bodyState[];                 // set58_bodyState
extern const s16 set58_sazanamiOffsets[];    // set58_sazanamiOffsets, indexed by timer (x, y pairs)
extern const u16 set58_cgIdsA[];             // set58_cgIdsA, indexed by data_0212c7c8[1]
extern const u16 set58_cgIdsB[];             // set58_cgIdsB, indexed by data_0212c7c8[1]
extern s32 em12_typeMasks;                    // game flag word
extern KnifeObjAffineSrcData scrollArgs;     // scrollArgs

extern "C" int func_02081b64(void);          // unmangled, returns non-zero when the scene check passes
void set58_actionInit(Entity *e); // 0x020742cc, defined in set58_7.cpp
void setYouseiEffect(Entity *e); // 0x020742e4, defined in set58 later

#endif
