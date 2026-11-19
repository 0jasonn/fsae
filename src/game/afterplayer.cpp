#include "game/afterplayer.h"

// Player entity fields past the common Entity block that AfterPlayer counts down.
typedef struct PlayerEntityVars {
    u8 unk_00[0x70];
    u8 stunCounter;  // 0x70
    u8 unk_71;
    u16 cooldown;    // 0x72
} PlayerEntityVars;

// AfterPlayer (0x020548f4): end-of-frame bookkeeping of every player: counts the timers down, clears the per-frame flags and
// runs the player entity's post-update, then rotates the entity list.
void AfterPlayer(void) {
    u8 i;
    PlayerData *player;

    data_0212c4e8 = 0;
    for (i = 0; i < gameState.playerCount; i++) {
        player = &playerWork[i];
        if (player->entity != NULL) {
            if (player->unk_14 != 0) {
                player->unk_14--;
            }
            if (player->unk_1a != 0) {
                if ((((u32)player->paletteBits << 25) >> 29) == 0 || !(player->hitFlags & 0x20)) {
                    func_0208919c(player->entity);
                }
            }
            if (VARS(PlayerEntityVars, player->entity)->cooldown != 0) {
                VARS(PlayerEntityVars, player->entity)->cooldown--;
            }
            if (player->unk_8a != 0) {
                player->unk_8a--;
            }
            player->unk_07 &= 0x7f;
            player->entity->contactFlags &= 0x7f;
            player->unk_27 = player->unk_1a = player->unk_34 = 0;
            player->unk_0a &= 0xf;
            player->statusFlags &= 0xfffd;
            player->unk_0f &= 0xef;
            func_020855bc(player->entity);
            if (VARS(PlayerEntityVars, player->entity)->stunCounter != 0) {
                VARS(PlayerEntityVars, player->entity)->stunCounter++;
            }
            if (player->unk_30 != 0) {
                player->unk_30--;
            }
        }
    }
    RotateObjWork(1);
}
