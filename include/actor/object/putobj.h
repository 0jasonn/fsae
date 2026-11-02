#ifndef WIP_A_PUTOBJ_H
#define WIP_A_PUTOBJ_H

#include "engine/functions.h"
#include "actor/enemy/enemycommon.h"
#include "actor/object/set_init.h"

// Links of the active object list: the first two words of every object.
typedef struct PutObjNode {
    struct PutObjNode *prev;  // 0x00
    struct PutObjNode *next;  // 0x04, NULL when the pool slot is free
} PutObjNode;

// Fields of a parent object that PutObjWork updates when a child goes away.
typedef struct PutObjOwner {
    u8 pad_00[0x62];
    u16 childCount;  // 0x62
    u16 childFlags;  // 0x64
} PutObjOwner;

extern const u32 flagBits[];
extern const u16 data_020dd0d0[];
extern const u16 *const data_020dd068[];

extern PutObjNode *data_0212c52c;  // tail of the active object list
extern u8 data_02134dd0[];         // free pool slot stack
extern u8 data_021348d4;           // free pool slot count
extern u8 data_0212f890[];         // object pool
extern u8 data_02134290[];         // end of the enemy part of the pool
extern u8 data_0212c4f4;
extern u8 data_0212c4cc;

#endif
