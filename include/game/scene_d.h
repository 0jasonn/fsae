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

void Scene_FollowCameraTarget(void);
int Scene_UpdateSlotWait(s32 slot, s32 effectId);
void Scene_StartSlotEffect(s32 slot, s32 effectId);
void Scene_StartSlotEntity(s32 slot, s32 index, s32 flags);
void Scene_UpdateStep(void);
void Scene_SetupGraphics(void);
void Scene_FinishStartup(void);
void Scene_NoOp(void);
void Scene_ReleaseResources(void);
void Scene_UpdatePlayerInput(void);
void Scene_CheckPlayerSlots(void);
void Scene_ResetPaletteA(void);
void Scene_ResetPaletteB(void);
void func_0202a60c(void);
void func_0204bbb8(void);
void func_0204bb9c(void);
void func_02050ac4(void);
void func_02082ee0(s32 a);
void Scene_FlushDirtyTiles(void);
void Scene_LoadBackground(s32 index);
void func_0204c4bc(u16 index, const void *src);
void func_0204c3a4(const void *a, const void *b, const void *c, const void *d, u16 e, const void *f);
void func_020845b0(u32 dest, void *src, u16 size);
void OSi_CpuClear32(u32 value, void *dst, u32 size);
void func_0204e690(const void *list, void *param);
void Scene_SpawnPatternA(Entity *e);
void Scene_SpawnPatternB(Entity *e);
void Scene_SpawnPatternC(Entity *e);
void Scene_SpawnPatternD(void);
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
void func_02083694(u32 layer, u16 index, u32 size);
void Scene_StoreTileIndices(const u16 *pos, u32 layer0, u32 layer1);
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
void func_0205069c(Entity *e, const u16 *bounds, s32 flags);
void func_020909c8(void);
void *func_0208da4c(void);
int func_0208de54(void *a);
void func_02050910(void);
void func_0202a60c(void);
void func_02050ac4(void);
void func_020830ec(void);
void MIi_CpuClearFast(u32 value, void *dst, u32 size);
u32 func_0202a754(u32 a, u32 b);
void func_02076804(const void *list);
void State_ClearWorkBuffers(void);
void func_0204bb9c(void);
void func_0204bbb8(void);
void func_02029b38(s32 a);
void func_02029fe8(s32 a);
void func_02029d0c(s32 a, s32 b);
void GX_DispOff(void);
void GX_DispOn(void);

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
void func_02029a50(void *dst, u32 size);
void func_020a1a1c(void *a);
void Scene_SpawnPatternE(Entity *e);
void Scene_SpawnPatternF(Entity *e);
void Scene_SpawnPatternG(Entity *e);
void Scene_SpawnPatternH(Entity *e);
void Scene_SpawnPatternI(Entity *e);
void Scene_SpawnPatternJ(Entity *e);
void Scene_ResetOverlayState(void);
void Scene_SetFlag5(void);
void Scene_ClearFlag5(void);
void Scene_CallStateHandler(void);
void Scene_QueueSelect(u8 index);
void Scene_UpdatePlayerSelect(void);
void Scene_BeginSelection(s32 index);
void Scene_ProcessQueue(void);
void Scene_InitObjects(s32 index, s32 unused, s32 value);
void MI_CpuFill(void *dst, u32 value, u32 size);
void func_020a1a30(void *a, const void *b);
void func_020a2138(void *a, s32 b);
void func_020a1a88(void *a, u16 index, s32 b, s32 c, s32 d);
extern u8 data_0216f020[];
extern const u8 data_0211476c[];
void func_020a1c60(void *a, s32 *x, s32 *y, s32 *z, s32 *w);
void func_020a22cc(void *a);
int Scene_CopyTileRows(void);
void func_020545a8(void);
void func_02049f38(s32 a);
extern u8 data_021369a0[];

#endif
