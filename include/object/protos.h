#ifndef WIP_F_PROTOS_H
#define WIP_F_PROTOS_H

// Prototypes and shared data used by src/wip/F/*.cpp that engine/functions.h does not declare yet
// (to be moved there by the reviewer).
#include "engine/functions.h"

// 0x02085890 (thumb), returns nonzero when the spot is blocked; (entity, table, x, y)
int func_02085890(Entity *e, const u8 *table, u16 x, u16 y);
// 0x020811a8, nonzero while the VRAM group load is pending (original VGroupLoadWait(OBJ_WORK_*))
int VGroupLoadWait(Entity *e);
// 0x02084110 (thumb), bit mask of the players in the warp (bits 0..3); the warp code passes the entity in r0
// 0x02099d88, class method Knife::Single::SinglePlay::SetWarpInfo(unsigned char, unsigned char)
extern "C" void Knife_Single_SinglePlay_SetWarpInfo(void *self, u8 a, u8 b);

// 0x02083d18 (thumb), hit/position test (entity, dx, dy)
int func_02083d18(Entity *e, int dx, int dy);

// 0x0205e114, original warphole_exit(OBJ_WORK_*), defined in src/object/warphole_3.cpp
void warphole_exit(Entity *e);

// Grid origin used to turn world positions into map cells (data_0212c648, u16 pair at +0x18 / +0x1a)
typedef struct WipGridOrigin {
    u8 unk_00[0x18];
    u16 originX;
    u16 originY;
} WipGridOrigin;
extern WipGridOrigin data_0212c648;

// Byte view of data_0212c7c8 (game state; UnkStruct_0212c7c8 in engine/player.h only names its first bytes)
extern u8 data_0212c7c8[];

#endif
