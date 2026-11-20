#include "game/frame_load.h"
#include "engine/local_player_index.h"
#include "engine/em12_type_masks.h"

// MPlayerSet(FRAME_INFO_*) (0x0204c950): picks the start cells of the players (a fixed layout in a special mode, otherwise
// one of the frame's start layouts, shuffled in a normal game), creates the player markers and makes the local one the
// camera target.
void MPlayerSet(FRAME_INFO_ *frame) {
    u8 cells[8];
    u8 *dst = cells;
    const u8 *layout;
    const u8 *layouts;
    u8 *pair;
    u32 i;
    u32 count;
    u32 k;
    u32 j;

    if (gameState.active != 0 && (gameState.phaseFlags & 0x20)) {
        layout = data_02103e84 + ((gameState.phaseFlags & 0xf) << 3);
        for (i = 0; i < 8; i++) {
            dst[i] = *layout++;
        }
        em12_typeMasks[0] |= 1;
    } else {
        layouts = (const u8 *)frame->infoRows[6];
        if (layouts == NULL) {
            layout = frame->unk_02 + 10;
        } else {
            count = layouts[0];
            layout = layouts + 1;
            layout += (Random() % count) * 8;
        }
        for (i = 0; i < 8; i++) {
            dst[i] = *layout++;
        }
        if (gameState.active == 0) {
            for (i = 0; i < 4; i++) {
                j = Random() & 3;
                k = dst[i * 2];
                dst[i * 2] = dst[j * 2];
                dst[j * 2] = k;
                k = dst[i * 2 + 1];
                dst[i * 2 + 1] = dst[j * 2 + 1];
                dst[j * 2 + 1] = k;
            }
        }
    }
    pair = cells;
    for (i = 0; i < gameState.playerCount; i++) {
        MPlayerInit(i, pair[0], pair[1]);
        playerWork[i].entity->health = gameState.health[i];
        pair += 2;
    }
    MIi_CpuCopy16(cells, gameState.startCells, 8);
    mapState.target = playerWork[localPlayerIndex].entity;
}
