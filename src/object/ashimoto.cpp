#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/objdecls_f.h"

// Ashimoto check (module ashimoto). Address -> name:
//   0x0205a8e8 AshimotoCheck (original name)

// Cell codes of a player: u16 entries at 0x40, 0x44, ... 0x80 (every other halfword of the player record).
#define CELL_AT(player, k) (*(u16 *)((u8 *)(player) + (k) * 2 + 0x40))

ARM void AshimotoCheck(Entity *e) {
    u16 cell;
    PlayerData *player;
    int base;
    int i;
    int k;

    base = GetBgBuffAdrs(e->layer);
    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        player = &data_0212ceb0[i];
        if (player->entity == NULL) {
            continue;
        }
        if ((player->entity->x.HALF.HI >> 4) != (e->x.HALF.HI >> 4)) {
            continue;
        }
        if ((player->entity->y.HALF.HI >> 4) != (e->y.HALF.HI >> 4)) {
            continue;
        }
        if ((player->entity->layer >> 14) != (e->layer >> 14)) {
            continue;
        }
        for (k = 0; k <= 0x20; k += 2) {
            cell = CELL_AT(player, k);
            if (cell == 0xffff) {
                continue;
            }
            if (*(u8 *)(base + cell + 0x2004) != 0xf) {
                player->entity->x.HALF.HI = (((u32)cell << 26) >> 22) + 8;
                player->entity->y.HALF.HI = ((CELL_AT(player, k) & 0xfc0) >> 2) + 6;
                break;
            }
            if (k == 0x1e) {
                PlStartPosSet(player->entity);
            }
        }
    }
}
