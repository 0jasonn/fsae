#ifndef UNKNOWN_A_BOSS_02038544_H
#define UNKNOWN_A_BOSS_02038544_H

#include "engine/entity.h"
#include "engine/player.h"

typedef struct Vars_02038544 {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *unk_64;
    /* 68 */ u8 unk_68[4];
    /* 6c */ u16 unk_6c;
    /* 6e */ u8 unk_6e[0xe];
    /* 7c */ u8 unk_7c;
    /* 7d */ u8 unk_7d;
} Vars_02038544;
#define V(e) VARS(Vars_02038544, e)

#ifdef __cplusplus
extern "C" {
#endif
int func_020849c8(Entity *e);
int func_02084a30(Entity *e);
void func_02084ab8(Entity *e, int a);
void func_02083c84(Entity *e);
void func_02038a88(Entity *e);
u8 func_02084fd0(Entity *e, Entity *target);
void *func_0208da4c(void);
int func_0208de54(void *a);
u8 *func_02093b5c(void);
u8 func_02045aa0(void);
void func_02084f54(Entity *e);
void Boss_RandomizeDirection(Entity *e);
Entity *func_02084f98(Entity *e, int a, int b);
u8 func_02045a8c(u8 a);
void CopyPosition(Entity *e, Entity *other);
#ifdef __cplusplus
}
#endif

extern const EntityFunc data_020d1868[];
extern const EntityFunc data_020d1880[];
extern const u16 data_020d1820[];
extern const u8 data_020d1828[];
extern const u8 data_020d18b4[];
extern const EntityFunc data_020d18bc[];
extern const EntityFunc data_020d195c[];
extern const EntityFunc data_020d1a34[];
extern const u8 data_020d19b8[];
extern const EntityFunc *const data_020d19ec[];
extern u16 data_0212c58c[];
extern u8 data_0212ceb2[];
extern u8 data_0212ceca[];
extern u8 data_0212cee4[];
extern u16 data_0212c5bc;
extern const s8 data_020d1844[];

#endif
