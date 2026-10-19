#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"

// Set09 actor (module set09). Address -> name:
//   0x02062bb8 Set09, 0x02062bd4 set09_init, 0x02062ce4 set09_wait, 0x02062d90 set09_initset,
//   0x02062dc4 set09_move, 0x02062e14 set09_wait2 (original names)

typedef struct Vars_Set09 {
    /* 00 */ u8 unk_00[0x62];
    /* 62 */ u16 unk_62; // counter, incremented by set6b_setenemy
    /* 64 */ u16 unk_64; // index passed to CountBits / func_02084634
    /* 66 */ u8 unk_66[2];
    /* 68 */ u32 typeBits; // bits from ParseTypeBits(type), tested against em12_typeMasks[areaIndex]
    /* 6c */ u8 unk_6c[4];
    /* 70 */ const u16 *info; // table from GetInfoAdrs, 8-byte entries ended by 0xffff
} Vars_Set09;

extern const EntityFunc data_020d9f38[]; // indexed by e->action
extern u32 em12_typeMasks[]; // one mask per area
extern "C" void GetCellsInRandomSet(u16 cell, u16 w, u16 h);
void BgmSet(void);
void set6b_setenemy(Entity *e, u8 index);

ARM void Set09(Entity *e) {
    data_020d9f38[e->action](e);
}
