#ifndef UNKNOWN_ENEMY_020347DC_H
#define UNKNOWN_ENEMY_020347DC_H

#include "engine/player.h"

typedef struct Vars_020347dc {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *aimTarget;
    /* 68 */ u8 unk_68[6];
    /* 6e */ u16 phaseFlags;
    /* 70 */ Entity *petal;
    /* 74 */ Entity **segmentSlot; // slot in the parent's segment list
    /* 78 */ u8 unk_78[4];
    /* 7c */ u16 orbitRadius;
    /* 7e */ u8 eventBitIndex;
    /* 7f */ u8 cycleTimer;
} Vars_020347dc;
#define V(e) VARS(Vars_020347dc, e)

typedef struct Vars_Event {
    /* 00 */ u8 unk_00[0x7d];
    /* 7d */ u8 eventFlags;
} Vars_Event;
#define VE(e) VARS(Vars_Event, e)

typedef struct Vars_Controller {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u8 flowerCount;
} Vars_Controller;
#define VCT(e) VARS(Vars_Controller, e)

typedef struct UnkStruct_021348c0 {
    s32 retargetTimer;
    s32 lastPlayer;
} UnkStruct_021348c0;
extern UnkStruct_021348c0 em2d_retargetState;

extern const EntityFunc em2d_type0Actions[];
extern const EntityFunc em2d_type1Actions[];
extern const u8 em2d_healthType0[];
extern const u8 em2d_healthType1[];
extern const u8 em2d_healthType2[];
extern const u16 em2d_demoSpeeds[];
extern const u16 em2d_thirdDemoSpeeds[];
extern const s8 em2d_dieSway[];
extern const s8 em2d_attackZ[];
extern const u8 em2d_type1Hitbox[];
extern const u8 em2d_openHitbox[];
extern const u8 em2d_petalColors[][3];
extern const s8 em2d_seedOffsets[];
extern const u8 em2d_rupeeItems[];

typedef struct Vars_SegmentList {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ Entity *segmentA;
    /* 74 */ Entity *segmentB;
    /* 78 */ Entity *segmentC;
} Vars_SegmentList;
#define VS(e) VARS(Vars_SegmentList, e)
extern const u8 em2d_closeHitbox[];
extern const s16 trigTable[];
extern const u32 flagBits[];



#endif
