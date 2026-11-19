#include "engine/functions.h"
#include "global.h"
#include "game/magne.h"
#include "game/sprite_bits.h"

// magneMove (0x02049dac): per-frame update of a player's magnet shadow. It follows the player's flip flags, plays a
// sound every 8 frames and copies the player's palette/frame state; when the player no longer owns it (bit 0 of
// playerWork[i].unk_0f is clear) it unregisters itself and removes the entity.
void magneMove(Entity *e) {
    Entity *player = *(Entity **)&data_0212ced8[(s16)e->type * 0x94];
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
        SPRITE_FLAGS(e)->flag2 = SPRITE_FLAGS(player)->flag2;
        SPRITE_FLAGS(e)->flag3 = SPRITE_FLAGS(player)->flag3;
        e->unk_21 = player->unk_21 - 0x7b;
        e->frame = player->frame;
        e->unk_2f = player->unk_2f;
    } else {
        *(Entity **)&data_0212cedc[(s16)e->type * 0x94] = NULL;
        PutObjWork(e);
    }
}
