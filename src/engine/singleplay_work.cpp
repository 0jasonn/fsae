#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/player.h"
#include "engine/singleplay_work_api.h"

// Knife::Single::SinglePlay::SinglePlayWork (the warp pair work item, not the controller singleton), 0x02099da8 to
// 0x02099ed8 and PlayerChange: the constructor, Initialize and PlayerChange. The fields are the two player pointers,
// their data pointers, the entities they point at, and the differences of their positions.

typedef struct SpWorkPair {
    PlayerData *player0;    // 0x00
    PlayerData *player1;    // 0x04
    void *data0;            // 0x08: data_0212caf0 or data_0212cb60
    void *data1;            // 0x0c
    Entity *entity0;        // 0x10: player0->entity
    Entity *entity1;        // 0x14: player1->entity
    u16 unk_18;             // 0x18
    u16 unk_1a;             // 0x1a
    u16 unk_1c;             // 0x1c
    u16 unk_1e;             // 0x1e
    u16 unk_20;             // 0x20
    u16 unk_22;             // 0x22
    s16 diffX;              // 0x24: entity0 x minus entity1 x (negated by PlayerChange)
    s16 diffY;              // 0x26
    s16 distX;              // 0x28: absolute diffX
    s16 distY;              // 0x2a: absolute diffY
    u16 unk_2c;             // 0x2c
    u16 unk_2e;             // 0x2e
    u16 unk_30;             // 0x30
    u16 unk_32;             // 0x32
    u16 unk_34;             // 0x34
    u16 unk_36;             // 0x36
    u8 unk_38;              // 0x38
    u8 unk_39;              // 0x39
    u8 nearFlag;            // 0x3a: set when both distances are below 0x20
    u8 unk_3b;              // 0x3b
    u8 unk_3c;              // 0x3c
} SpWorkPair;

s32 abs_s32(s32 value);
extern u8 data_0212caf0[];
extern u8 data_0212cb60[];

// SinglePlayWork::SinglePlayWork() (0x02099da8): clears the pointers, then the halfword and byte fields
void Knife_Single_SinglePlay_SinglePlayWork_SinglePlayWork(void *self) {
    SpWorkPair *w;

    w = (SpWorkPair *)self;
    w->player0 = NULL;
    w->player1 = NULL;
    w->data0 = NULL;
    w->data1 = NULL;
    w->entity0 = NULL;
    w->entity1 = NULL;
    w->unk_18 = 0;
    w->unk_1c = 0;
    w->unk_1e = 0;
    w->unk_20 = 0;
    w->unk_22 = 0;
    w->diffX = 0;
    w->diffY = 0;
    w->distX = 0;
    w->distY = 0;
    w->unk_2c = 0;
    w->unk_2e = 0;
    w->unk_30 = 0;
    w->unk_32 = 0;
    w->unk_34 = 0;
    w->unk_36 = 0;
    w->unk_38 = 0;
    w->unk_39 = 0;
    w->nearFlag = 0;
    w->unk_3b = 0;
    w->unk_3c = 0;
}

