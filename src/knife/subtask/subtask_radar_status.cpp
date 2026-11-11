#include "engine/functions.h"
#include "engine/radar_status.h"

// GetSubtaskRadarStatus(SUBTASK_RADAR_WORK*) (0x020a3570, original name from the debug build): collects the values the
// radar screen shows: stage, area, time, the three power levels of the local player, the position of every player
// and the goal marker, scaled to the radar
void GetSubtaskRadarStatus(SubtaskRadarStatus *out) {
    u8 *app = (u8 *)KnifeApp_getInstance();
    u8 *singlePlay = Knife_Single_SinglePlay_GetInstance();
    s32 player;
    s32 mode;
    s32 i;
    PlayerData *pw;

    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        player = localPlayerIndex;
    } else {
        player = *singlePlay;
    }
    mode = gameState.gameMode;
    if (gameState.difficulty != 0) {
        mode = 2;
    }
    out->stage = data_020de6c4[mode];
    out->area = gameState.phaseTimer;
    out->time = gameState.frameCount / 60;
    out->power = (u32)(data_0212c53c->unk_3e << 30) >> 30;
    out->defense = (u32)(data_0212c53c->unk_3e << 28) >> 30;
    out->speed = (u32)(data_0212c53c->unk_3e << 26) >> 30;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        out->kakera = data_0212c830[player];
    } else {
        out->kakera = gameState.playerFlag68[0];
    }
    out->player = player;
    for (i = 0; i < 4; i++) {
        if (i >= gameState.playerCount) {
            out->present[i] = 0;
            out->pos[i].x = 0;
            out->pos[i].y = 0;
            continue;
        }
        pw = &playerWork[i];
        if (pw != NULL && pw->entity != NULL) {
            out->present[i] = 1;
            out->pos[i].x = (pw->entity->x.HALF.HI * 0x90) / 0x3f0;
            out->pos[i].y = (pw->entity->y.HALF.HI * 0x90) / 0x3f0;
            if (((Knife::Hud::HudManager *)(app + 0x1f8))->isJustStartedCallAnim(i)) {
                out->slot[i] = 0;
            }
        }
    }
    out->unk_60 = (gameState.targetX * 0x90) / 0x3f0;
    out->unk_64 = (gameState.targetY * 0x90) / 0x3f0;
}
