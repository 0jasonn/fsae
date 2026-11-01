#include "engine/functions.h"
#include "game/time_bonus.h"
#include "global.h"

extern const u16 timeBonusThresholds[];
extern const u16 timeBonusThresholdsAlt[];
extern const u16 *const timeBonusValues[];
extern const u16 *const timeBonusValuesAlt[];

BOOL warp_check(void) {
    u8 i;
    for (i = 0; i < data_0212c7c8.playerCount; i++) {
        if (!(data_0212ceb0[i].statusFlags & 1)) {
            if (data_0212ceb0[i].entity->health != 0) {
                continue;
            }
        }
        return FALSE;
    }
    return (func_020280e0() & 0xf) == data_0212c7c8.unk_6f;
}

void time_bonus(void) {
    u32 seconds = data_0212c7c8.frameCount / 60;
    int playerCount = data_0212c7c8.playerCount;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        playerCount = 1;
    }
    TelopRequest(0x3ea);
    telopRequest.unk_08 = (u16)(seconds / 60);
    telopRequest.unk_0c = (u16)(seconds % 60);
    telopRequest.unk_10 = get_time_bonus();
    telopRequest.unk_14 = (u16)playerCount;
}

u16 get_time_bonus(void) {
    u8 i;
    u32 seconds = data_0212c7c8.frameCount / 60;
    const u16 *const *bonusValues = timeBonusValues;
    const u16 *bonusThresholds = timeBonusThresholds;
    if (data_0212c7c8.gameMode == 6) {
        bonusThresholds = timeBonusThresholdsAlt;
        bonusValues = timeBonusValuesAlt;
    }
    for (i = 0; i < 7; i++) {
        if (seconds < bonusThresholds[i]) {
            break;
        }
    }
    return bonusValues[data_0212c7c8.playerCount][i];
}
