#ifndef WIP_C_DECLS_H
#define WIP_C_DECLS_H

// Declarations shared by the implementer C files (src/wip/C/*.cpp) that are not in engine/functions.h yet.

#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "types.h"
#include "game/stagesel.h"
#include "engine/misc_d.h"

extern "C" s32 WXC_GetStateCode(void);
int CommFrameSync(void);
void CommUpdateJoy(void);
void CommFrameUpdate(void);
extern "C" {
s32 Knife_Message_selectionDialog_getResult(void *a);
void func_0208b644(Entity *e);
void EffectSet(Entity *e, int kind, int arg);
void func_0208af0c(Entity *e);
void func_0208b668(Entity *e);
int func_02085294(void);
u8 ClearKeyCheck(void);
int ZeldaFadeFlagGet(void);
void func_0202809c(void);
void SoundInit(void);
void Knife_Single_SinglePlay_Initialize(u8 *self);
}
void ssel_char_scr(u8 index);

// Stage select object table (data_02171d58). Fields used so far are named.
typedef struct SselObjTable {
    /* 00 */ u8 unk_00;
    /* 01 */ u8 tutorialActive; // nonzero while the tutorial save dialog runs
    /* 02 */ u8 tutorialTimer; // frames left before the tutorial save dialog closes
    /* 03 */ u8 unk_03[5];
    /* 08 */ Entity *unk_08;
    /* 0c */ Entity *unk_0c;
    /* 10 */ s32 unk_10;
    /* 14 */ Entity *pleaseWait;
    /* 18 */ u32 unk_18;
    /* 1c */ Entity *unk_1c;
    /* 20 */ u32 loadFlags; // bit 0: the character graphics pointers are set up
} SselObjTable;
extern SselObjTable data_02171d58;

// Per-player flags, 8 bytes each, starting right after UnkStruct_0212c7c8 (enemyTypeFlags)
typedef struct SselPlayerFlags {
    /* 00 */ u32 flags;
    /* 04 */ u8 unk_04;
    /* 05 */ u8 unk_05;
    /* 06 */ u16 unk_06;
} SselPlayerFlags;

// One save slot (data_021350b0, 0x50 bytes each); the slot index is data_02171df8[4]
typedef struct SselSaveSlot {
    /* 00 */ u32 flags;
    /* 04 */ u8 unk_04;
    /* 05 */ u8 unk_05;
    /* 06 */ u16 unk_06;
    /* 08 */ u8 unk_08[0x40];
} SselSaveSlot;
extern u8 data_021350b0[];
extern u32 data_0212c858[];
extern u8 data_02171df8[];
extern u8 data_02171d7c[];
extern u16 data_0212c58c[];
// Scroll table entries (data_020dc67c): two u16 per step, copied to the stack by stagesel_scroll
typedef struct SselScrollPair {
    u16 first;
    u16 second;
} SselScrollPair;
extern const SselScrollPair data_020dc67c[5];
int Save4SwordsFile(u8 slot);
extern SselPlayerFlags enemyTypeFlags[];

extern u8 data_0212c4d0;
extern u8 data_0212c4b8;
extern const u8 data_020dc704[];
extern const EntityFunc data_020dca78[];
extern const EntityFunc data_020dca60[];
extern const u8 data_020dca68[];
extern const u8 data_020dca70[];
extern const u8 data_020dcad9[];
extern const u8 data_020dcad0[];
extern const u16 data_020dcac8[];
extern const u8 data_020dcb08[];
extern const u8 data_020dcb00[];
extern const u8 data_020dcab4[];
extern const EntityFunc data_020dcaec[];
void func_0208b628(Entity *e);
void SKemuriSet(Entity *e);
extern u8 data_0212ceb2[];
extern u8 data_0212ceb4[];
extern u8 data_0212ced8[];
extern u8 data_0212cedc[];
extern u8 data_0212cebf[];
extern const u8 data_020dc707[];
void sword_move(Entity *e);
void tama00_hajikiInit(Entity *e);
void tama04_hajikiInit(Entity *e);
int CalcRupeeDiff(u8 index);
void kabutowari(Entity *e);
void *zMalloc(u16 size);
u8 GetRandomTakara(u8 **list, u8 type);
void set_takara2(u8 kind, u16 value, Entity *e);
extern const EntityFunc data_020dc71c[]; // sword action table, indexed by e->action
extern u8 data_0212c4dc;
extern u8 data_0212c4e4;
extern u16 data_021355a0;
extern u8 data_0212c500;
extern u8 localPlayerIndex;
extern u8 data_021349c0[]; // effect state block, u16 timer at +4
extern u8 data_0212c9a8[];
// Frame counts of the stage select messages (11 words, copied to the stack by stagesel_message)
typedef struct SselMessageTimes {
    u32 frames[11];
} SselMessageTimes;
extern const SselMessageTimes data_020dc690;
extern u8 data_02116720[]; // stage select message parameter block
extern u8 data_02148fa0[];
extern u8 data_02140fa0[];
extern u8 data_02150fa0[];
extern const u32 data_021167c4[]; // pairs of (source, size) for the character graphics

// Treasure chest table: 32 entries of (id, handler index, flags); searched by TakaraOpen
typedef struct TakaraEntry {
    /* 00 */ u16 id;
    /* 02 */ u8 unk_02; // low 5 bits index the handler table
    /* 03 */ u8 unk_03;
} TakaraEntry;
typedef void (*TakaraHandler)(TakaraEntry *entry, Entity *e, u16 id);
extern TakaraEntry data_02134c30[32];
extern const TakaraHandler data_02116800[];
extern const u32 flagBits[];
extern u32 data_0213491c;
extern u8 *data_02117a68[];
extern u8 *data_02117a48[];
extern u8 *data_02117a28[];
extern u8 data_0212c81c[];
extern u32 data_0212c54c;
extern s32 data_0212c7d4[];
extern u8 data_02117b20[];
extern u8 data_02117a0c[];

#endif
