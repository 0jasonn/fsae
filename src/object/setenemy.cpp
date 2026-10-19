#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"

// Spawns an enemy from the Set09 table (module set09 helper). Address -> name:
//   0x02062f24 set6b_setenemy (original name setenemy)

typedef struct Vars_Set09 {
    /* 00 */ u8 unk_00[0x62];
    /* 62 */ u16 spawnCount; // number of spawned objects
    /* 64 */ u16 unk_64; // bit word, OR-ed with flagBits[slot]
    /* 66 */ u8 unk_66[2];
    /* 68 */ u32 typeBits;
    /* 6c */ u8 unk_6c[4];
    /* 70 */ const u16 *info; // table from GetInfoAdrs, 8-byte entries
} Vars_Set09;

typedef struct Vars_Setenemy_Child {
    /* 00 */ u8 unk_00[0x68];
    /* 68 */ u8 slot; // parent slot + 1
    /* 69 */ u8 unk_69[7];
    /* 70 */ u8 objIdCopy;
    /* 71 */ u8 typeCopy;
    /* 72 */ u8 type2Copy;
} Vars_Setenemy_Child;

extern "C" s32 func_02084634(u16 a);
extern const u32 flagBits[];

ARM void set6b_setenemy(Entity *e, u8 index) {
    Entity *obj;
    s32 slot;

    slot = func_02084634(VARS(Vars_Set09, e)->unk_64);
    obj = GetObjWork();
    if (obj == NULL) {
        return;
    }
    if (func_02085024(obj, VARS(Vars_Set09, e)->info + slot * 4, e->areaIndex) == 0) {
        return;
    }
    VARS(Vars_Setenemy_Child, obj)->objIdCopy = obj->objId;
    VARS(Vars_Setenemy_Child, obj)->typeCopy = obj->type;
    VARS(Vars_Setenemy_Child, obj)->type2Copy = obj->type2;
    obj->linkedEntity = e;
    VARS(Vars_Setenemy_Child, obj)->slot = slot + 1;
    obj->areaIndex = e->areaIndex;
    obj->objKind = 6;
    obj->objId = 0x0a;
    obj->subtimer = index;
    VARS(Vars_Set09, e)->spawnCount = VARS(Vars_Set09, e)->spawnCount + 1;
    VARS(Vars_Set09, e)->unk_64 = VARS(Vars_Set09, e)->unk_64 | (u16)flagBits[slot];
}
