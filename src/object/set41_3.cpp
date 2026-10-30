#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

// Set41 family, third unit (module set41). Address -> name:
//   0x0206c594 set41_move (original name)
// set41_wait / set41_appear are in set41_2.cpp, set41_init in set41.cpp.

extern u32 em12_typeMasks[];        // one mask per area (0x02134954)
extern const u32 flagBits[];        // flag per entity type (0x020cf9b8)
extern u8 localPlayerIndex;         // localPlayerIndex
extern u32 data_02134900;           // pending message flag, cleared once the message is requested
extern u8 data_0212c500;            // step index, 9 when the message can be shown

#define SPRITE_WORD(e) (*(u32 *)&(e)->spriteSettings)

typedef struct Vars_Set41Move {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u16 messageId; // message requested by the lever, 0x292 for the staff roll message
} Vars_Set41Move;

ARM void set41_move(Entity *e) {
    Entity *player;
    u8 facing;
    void *app;

    UpdateAnimationSingleFrame(e);
    if (e->unk_47 != 0) {
        app = KnifeApp_getInstance();
        if (KnifeApp_isWirelessMode(app) == 0 && e->unk_47 == 2) {
            if (*Knife_Single_SinglePlay_GetInstance() == 0) {
                data_0212ceb0[e->unk_47 - 1].unk_0a[1] = 0;
                e->unk_47 = 0;
                return;
            }
        }

        player = data_0212ceb0[e->unk_47 - 1].entity;
        em12_typeMasks[e->areaIndex] |= flagBits[e->unk_16];
        facing = GetFacingDirection(e, player);
        if ((facing & 0xf) != 0) {
            if (facing < 0x10) {
                SPRITE_WORD(e) |= 4;
            } else {
                SPRITE_WORD(e) &= ~4;
            }
        }
        if (localPlayerIndex == player->type || KnifeApp_isWirelessMode(app) == 0) {
            MessageRequest(VARS(Vars_Set41Move, e)->messageId);
            e->subtimer = 1;
        }
        e->unk_47 = 0;
        player->iframes = 0xf8;
        return;
    }

    if (data_02134900 == 0) {
        return;
    }
    if (data_0212c500 != 9 || VARS(Vars_Set41Move, e)->messageId != 0x292) {
        return;
    }
    MessageRequest(VARS(Vars_Set41Move, e)->messageId);
    data_02134900 = 0;
}
