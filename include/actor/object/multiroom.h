#ifndef WIP_C_MULTIROOM_H
#define WIP_C_MULTIROOM_H

#include "engine/functions.h"
#include "engine/entity.h"

// Scroll state block mapState as MultiRoomInit uses it. The first word is the entity the view follows.
typedef struct MultiRoomScroll {
    /* 00 */ Entity *target;
    /* 04 */ u8 unk_04[0xe];
    /* 12 */ s16 unk_12;
    /* 14 */ s16 unk_14;
    /* 16 */ u8 unk_16[2];
    /* 18 */ u16 originX;
    /* 1a */ u16 originY;
    /* 1c */ s16 offsetX;
    /* 1e */ s16 offsetY;
    /* 20 */ s16 scrollX;
    /* 22 */ s16 scrollY;
    /* 24 */ s16 startX;
    /* 26 */ s16 startY;
    /* 28 */ u16 limitX;
    /* 2a */ u16 limitY;
} MultiRoomScroll;
extern MultiRoomScroll mapState;

extern u8 triangleTable[];               // 0x021387a0, cleared by MultiRoomInit (size 0x800)
extern u16 data_0215dfa4[];              // 0x0215dfa4, cell index lists of the two layers
extern u16 data_02168fa8[];
extern u32 *const data_020d7110[];       // per-room map data
extern u16 *const data_020d714c[];       // per-room background animation, may be null
extern u8 data_02158fa0[];               // 0x02158fa0, layer buffers (first word: pointer to the screen block)
extern u8 data_02163fa4[];

extern "C" {
void bg2StSet(void);                     // 0x02057494
}
void BgAnmInit(u16 *a);                  // 0x02023cc0
void MultiRoomInit(u16 room);            // 0x02056f4c

#endif
