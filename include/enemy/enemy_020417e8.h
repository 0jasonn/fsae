#ifndef WIP_B_ENEMY_020417E8_H
#define WIP_B_ENEMY_020417E8_H

#include "engine/player.h"

// Overlay for the enemy whose functions start at 0x020417e8 (same family as the 0x0204112c file).
typedef struct Vars_020417e8 {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *target;
    /* 68 */ u8 unk_68[6];
    /* 6e */ u16 cycleTimer;       // counts down from 0x1e
    /* 70 */ u16 subPosX;          // scroll position, stepped by 8 per frame
    /* 72 */ u16 subPosY;          // scroll position, stepped by 8 per frame
    /* 74 */ u8 unk_74[2];
    /* 76 */ u16 phaseTimer;       // counts down from 0x12c in the parts sequence
    /* 78 */ u8 orbitOffsets[8];   // packed offsets: low nibble x, high nibble y, 0x88 = no offset
} Vars_020417e8;
#define W(e) VARS(Vars_020417e8, e)

// Overlay for an entity that owns two parts at 0x78 and 0x7c.
typedef struct Vars_Parts {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ Entity *partA;
    /* 7c */ Entity *partB;
} Vars_Parts;
#define VPARTS(e) VARS(Vars_Parts, e)

// Overlay for an entity that runs a phase sequence with a hold timer and a turn counter.
typedef struct Vars_Hold {
    /* 00 */ u8 unk_00[0x74];
    /* 74 */ u8 phase;
    /* 75 */ s8 turnStep;
    /* 76 */ u8 turnCount;
    /* 77 */ u8 unk_77;
    /* 78 */ u16 holdTimer;
    /* 7a */ u16 holdReload;
} Vars_Hold;
#define VH(e) VARS(Vars_Hold, e)

// Overlay for an entity that reads a command script from 0x70.
typedef struct Vars_Script {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ const u16 *script;
} Vars_Script;
#define VS(e) VARS(Vars_Script, e)

// Fields of a parent entity that its followers read.
typedef struct Vars_Parent {
    /* 00 */ u8 unk_00[0x7d];
    /* 7d */ u8 state;             // 1 while the parent is in its moving state
    /* 7e */ u8 unk_7e;
    /* 7f */ u8 triggerFlags;      // bit 0: raised by the parent, cleared by the follower
} Vars_Parent;

// The sprite settings word as this file uses bits 8-9: a separate 2-bit field.
typedef struct SpriteSettingsView {
    u32 low : 8;
    u32 b8 : 2;
    u32 high : 22;
} SpriteSettingsView;
#define SPRITE_VIEW(e) ((SpriteSettingsView *)&(e)->spriteSettings)

// Bit 2 of the sprite settings word on its own.
typedef struct SpriteBit2View {
    u32 low : 2;
    u32 bit2 : 1;
    u32 high : 29;
} SpriteBit2View;
#define SPRITE_BIT2(e) ((SpriteBit2View *)&(e)->spriteSettings)

typedef struct UnkStruct_0212c648 {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 unk_18;
    /* 1a */ u16 unk_1a;
} UnkStruct_0212c648;
extern UnkStruct_0212c648 data_0212c648;

typedef struct UnkStruct_0212c6b0 {
    /* 00 */ u8 unk_00[0x14];
    /* 14 */ Entity *head;         // first entity of the list walked by Enemy_UpdateChainInserts
} UnkStruct_0212c6b0;
extern UnkStruct_0212c6b0 data_0212c6b0;
extern u8 data_0212c6c0[];          // list sentinel

extern u16 data_0212c5bc;           // frame counter
extern u16 data_0212c574[3];        // scroll arguments for func_0205063c

void Enemy_SetDefaultAuxBytes(Entity *e);
void func_0205063c(u16 *pos, Entity *e);
void func_02085f98(Entity *e, int id);
void func_02085cf8(Entity *e);
void func_02085d34(Entity *e);
void func_0204be88(Entity *e);
void func_02042044(Entity *e);
void Enemy_CheckTileThenSpawnFx(Entity *e);
void func_02042dc8(Entity *e);
void Enemy_SpawnRandomGroup(Entity *e);
void Enemy_SetSpriteFromTable(Entity *e);
void func_02050390(Entity *child, Entity *e, int a, int b);
void EnemyFunctionHandler(Entity *e, const void *funcs);
void GenericKnockback(Entity *e, const void *funcs);
Entity *func_0204bdb8(int kind);
extern const u8 data_020d34d2[];
extern const u8 data_020d34ca[];
extern const u8 data_020d34da[];
int Enemy_SpawnPartPair(Entity *e);
Entity *func_0204bcc8(void);
Entity *func_0204bd00(void);
void func_0204c178(int kind, Entity *e);
u32 func_0208455c(u32 value);
extern const u8 data_020f26c0[];
extern const u32 data_020cf9b8[];
extern const u8 data_020f26c3[];
extern const u8 data_020d35e0[];
extern const u8 data_020d35fc[];
extern const EntityFunc data_020d35e4[];
extern const EntityFunc data_020d360c[];
extern const u16 data_020d35ec[];
extern const u16 *data_02103800[];
extern u8 data_021348ec[];
typedef struct RecordEntry {
    u16 a;
    u16 b;
    u16 c;
    u16 d;
    u16 e;
    u8 f;
    u8 g;
} RecordEntry;

typedef struct UnkStruct_02134b48 {
    /* 00 */ u8 state;
    /* 01 */ u8 unk_01[0x57];
    /* 58 */ const RecordEntry *record;
    /* 5c */ u16 recA;
    /* 5e */ u16 recB;
    /* 60 */ u16 recC;
    /* 62 */ u16 recD;
    /* 64 */ u16 recE;
    /* 66 */ u8 recF;
    /* 67 */ u8 recG;
} UnkStruct_02134b48;
extern UnkStruct_02134b48 data_02134b48;
extern const u8 data_020f270c[];
extern const u8 data_020f273c[];
void func_02029a50(void *p, int size);
void func_02043fec(Entity *e);
void func_02043f70(Entity *e);
void func_02043bf8(Entity *e, int a);
extern void (*const data_020d413c[])(void);
void func_02044324(u8 *state);
extern const void *data_020d35f4[];
u8 func_02086080(s16 x, s16 y, s16 dx, s16 dy);
void Enemy_StartScript(Entity *e);
void func_02043428(Entity *e);
void Enemy_RunScriptCommand(Entity *e);
void ProcessMovement(Entity *e);
int UpdateGravity(Entity *e, int a);
void *func_0208da4c(void);
int func_0208de54(void *a);
void func_02045f8c(Entity *e);
int func_020860dc(Entity *e);
int func_02083ca8(u16 cell, u16 key);
int func_02021c28(int id, u16 cell, u16 key);
Entity *CopyPosition(Entity *src, Entity *dst);
Entity *func_02045bd4(Entity *e, int kind, int flags);
void func_020852f8(Entity *e, int dist, int direction);


#endif
