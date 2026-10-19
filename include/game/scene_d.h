#ifndef WIP_D_MISC_D_RANGE_H
#define WIP_D_MISC_D_RANGE_H

#include "engine/misc_d.h"

// Effect state block (data_021349c0) entries used only by the functions in this range
#define EFFECT_STATE_ACTIVE_SLOT 0x0f // slot of the running effect, 0xff when none (guess)

// One 0x14-byte entry of data_02134d3c: the first word is the entity that owns the slot
typedef struct EffectSlot {
    /* 00 */ Entity *entity;
    /* 04 */ u8 unk_04[0x10];
} EffectSlot;
extern EffectSlot data_02134d3c[];

// Pairs of u16 (x and y bounds) indexed by player or effect number
extern const u16 data_02104a30[][2];
extern const u16 data_02104ab0[][2];

extern u32 data_0212c530;
extern const VoidFunc data_02104a90[];

extern const u8 data_020d80e0[];
extern const u8 data_020d80e3[];
extern const u8 data_020d80e6[];
extern const u8 data_020d80ec[];
extern const u8 data_020d80ef[];
extern const u8 data_020d80f2[];
extern const u8 data_020d80f8[];
extern const u8 data_020d80fb[];
extern const u8 data_020d80fe[];
extern const u8 data_020d8104[];
extern const u8 data_020d8109[];
extern u16 data_0213492c[];
extern const u16 data_02109484[];
extern const u16 data_0210948c[];
extern const u16 data_02109494[];
extern const u16 data_0210949c[];
extern const u16 data_021094a4[];
extern const u16 data_021094ac[];
extern const u16 data_021094b4[];
extern const u16 data_021094bc[];
extern const u16 data_021094c4[];
extern const u16 data_021094cc[];
extern const u16 data_021094d4[];
extern const u16 data_021094dc[];
void DispReset(void);
void func_02050ac4(void);
void func_0204bb9c(void);
void ObjMoveInit(void);

extern u8 data_0212ccb0[];
extern u8 data_0212cdb0[];
extern u8 data_0212dd90[];
extern u8 data_020d80d8[];
extern u8 data_021361a0[];
extern u8 data_0212c4e0;
extern u16 data_0212c514;
extern u16 data_0212c58c[];
extern u8 data_0212c9a8[];
extern u16 data_021355a0;
extern u8 data_02170504[];
extern u8 data_021369a0[];
extern u8 data_0217d36c[];
extern const u8 data_02104ad4[];
extern u8 data_0216fcfc[];
extern u8 data_0216fcfd[];
extern u8 data_0216fcfe[];
extern u8 data_0216fcff[];
extern u8 data_0212c4c8;
extern u32 data_0212c56c;
extern u32 data_0212c570;
extern u32 data_0212c528;

extern const u8 data_02111741[];
extern const u8 data_0211173c[];
extern const u8 data_020d8115[];
extern const u8 data_020d8110[];
extern const u8 data_021119e3[];
extern const u8 data_021119dc[];
extern const u8 data_020d8121[];
extern const u8 data_020d811c[];
extern const u8 data_02111c9f[];
extern const u8 data_02111c96[];
extern const u8 data_020d812d[];
extern const u8 data_020d8128[];
extern u8 data_02134980[];
extern u8 data_02171c84[];
extern const VoidFunc data_0211474c[];
extern u8 data_0216f020[];
extern const u8 data_0211476c[];
extern u8 data_021369a0[];

#endif
