#ifndef WIP_D_MISC_D_RANGE_H
#define WIP_D_MISC_D_RANGE_H

#include "engine/misc_d.h"

// Effect state block (data_021349c0) entries used only by the functions in this range
#define EFFECT_STATE_ACTIVE_SLOT 0x0f // slot of the running effect, 0xff when none (guess)

// One 0x14-byte entry of fairySlots: the first word is the entity that owns the slot
typedef struct EffectSlot {
    /* 00 */ Entity *entity;
    /* 04 */ u8 unk_04[0x10];
} EffectSlot;
extern EffectSlot fairySlots[];

// Pairs of u16 (x and y bounds) indexed by player or effect number
extern const u16 data_02104a30[][2];
extern const u16 fairyMoveTable[][2];

extern u32 opTitleState;
extern const VoidFunc opTitleTable[];

extern const u8 spawnList_053428_high[];
extern const u8 spawnList_053428_set[];
extern const u8 spawnList_053428_mid[];
extern const u8 spawnList_053484_high[];
extern const u8 spawnList_053484_set[];
extern const u8 spawnList_053484_mid[];
extern const u8 spawnList_0534e0_set[];
extern const u8 spawnList_0534e0_mid[];
extern const u8 spawnList_0534e0_high[];
extern const u8 spawnList_kazan2a1_set[];
extern const u8 spawnList_kazan2a1_clear[];
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
void ObjMoveInit(void);

extern u8 data_0212ccb0[];
extern u8 data_0212cdb0[];
extern u8 objAffineSet[];
extern u8 data_020d80d8[];
extern u8 data_021361a0[];
extern u8 data_0212c4e0;
extern u16 data_0212c514;
extern u16 data_0212c58c[];
extern u8 data_0212c9a8[];
extern u16 data_021355a0;
extern u8 titleDialogBuffer[];
extern u8 data_021369a0[];
extern u8 telopRequest[];
extern const u8 titleDialogData[];
extern u8 data_0216fcfc[];
extern u8 data_0216fcfd[];
extern u8 data_0216fcfe[];
extern u8 data_0216fcff[];
extern u8 data_0212c4c8;
extern u32 data_0212c56c;
extern u32 data_0212c570;
extern u32 data_0212c528;

extern const u8 spawnList_0537bc_set[];
extern const u8 spawnList_0537bc_clear[];
extern const u8 spawnList_0537f8_set[];
extern const u8 spawnList_0537f8_clear[];
extern const u8 spawnList_053834_set[];
extern const u8 spawnList_053834_clear[];
extern const u8 spawnList_053870_set[];
extern const u8 spawnList_053870_clear[];
extern const u8 spawnList_0538ac_set[];
extern const u8 spawnList_0538ac_clear[];
extern const u8 spawnList_0538e8_set[];
extern const u8 spawnList_0538e8_clear[];
extern u8 pauseState[];
extern u8 pauseDialogWindow[];
extern const VoidFunc pauseHandlerTable[];
extern u8 pauseDialogBuffer[];
extern const u8 pauseDialogRect[];
extern u8 data_021369a0[];

#endif
