#ifndef WIP_D_SET57_H
#define WIP_D_SET57_H

// Set57 actor fields and data (file-local to the D units of module set57; see src/wip/D/kenfuri.cpp and set57.cpp)

#include "engine/entity.h"

typedef struct Vars_Set57 {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u16 tileIndex; // value from set57_tileIds, compared with the BG cell in set57_move
    /* 7a */ u16 unk_7a;
    /* 7c */ u16 *cellPtr;  // BG buffer cell for this entity's grid position
} Vars_Set57;
#define V57(e) VARS(Vars_Set57, e)

typedef struct GridOrigin {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 unk_18;
    /* 1a */ u16 unk_1a;
} GridOrigin;
extern GridOrigin data_0212c648; // grid origin, see em12.h
extern const u8 set57_itemIds[];      // set57_itemIds, indexed by e->type
extern const u8 set57_paletteIndex[]; // set57_paletteIndex, indexed by e->type
extern const u16 set57_tileIds[];     // set57_tileIds, indexed by e->type
extern const EntityFunc set57_actions[]; // set57_actions, indexed by e->action

#endif
