#ifndef WIP_A_SET38_H
#define WIP_A_SET38_H

#include "engine/functions.h"
#include "engine/player.h"

// Actor fields of the Set38 family (file-local overlay, Entity fields are in engine/entity.h).
typedef struct Vars_Set38 {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u32 typeMask; // flagBits[type & 0x1f], ORed into em12_typeMasks[areaIndex] while held
} Vars_Set38;

// Link's entity (PlayerData.entity): the object it carries is stored at 0x6c, which Entity does not name.
typedef struct Vars_Carrier {
    /* 00 */ u8 unk_00[0x6c];
    /* 6c */ Entity *carried;
} Vars_Carrier;

extern const EntityFunc set38Table[];     // set38Table, indexed by action
extern const EntityFunc set38LiftTable[]; // set38LiftTable, indexed by subAction
extern const u8 set38Hitbox[];            // set38Hitbox
extern Entity *data_02134920;             // Set38 child currently linked to the player (shared global)
extern const u32 flagBits[];              // flagBits, one mask per type & 0x1f
extern u32 em12_typeMasks[];
extern u16 data_0212c594;                 // frame counter

int AssignObj(void *obj);                 // AssignObj(void*): C++ linkage in the original
extern "C" int func_02085c28(Entity *e);
extern "C" void func_02085fac(Entity *e);
extern "C" void func_02085fd0(Entity *e);
extern "C" void EffectSet(Entity *e, int kind, int arg);

void heart_throw_end(Entity *e);

#endif
