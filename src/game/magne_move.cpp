#include "engine/functions.h"
#include "global.h"
#include "game/magne.h"

// magneMove (0x02049dac): per-frame update of a player's magnet shadow. It follows the player's flip flags, plays a
// sound every 8 frames and copies the player's palette/frame state; when the player no longer owns it (bit 0 of
// playerWork[i].unk_0f is clear) it unregisters itself and removes the entity.
void magneMove(Entity *e) {
    Entity *player = playerWork[(s16)e->type].entity;
    if (data_0212cebf[(s16)e->type * 0x94] & 2) {
        e->spriteSettings.b16 = 1;
    } else {
        e->spriteSettings.b16 = 0;
    }
    if (e->timer-- == 0) {
        e->timer = 8;
        func_02085f98(player, 0x4f);
    }
    if (data_0212cebf[(s16)e->type * 0x94] & 1) {
        e->spriteSettings.flipX = player->spriteSettings.flipX;
        e->spriteSettings.b3 = player->spriteSettings.b3;
        e->unk_21 = player->unk_21 - 0x7b;
        e->frame = player->frame;
        e->unk_2f = player->unk_2f;
    } else {
        playerWork[(s16)e->type].weapon = NULL;
        PutObjWork(e);
    }
}
