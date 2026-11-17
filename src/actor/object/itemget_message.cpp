#include "engine/functions.h"
#include "engine/player.h"

extern const u16 data_02115ae0[];
extern u32 data_021348fc;
extern u8 localPlayerIndex;
// itemget_message, 0x02065e14. Requests the item message of the player's current item once per item: in a wireless game
// only on the machine of the player in question, and only when the item's bit is not yet set in the shown flags.
void itemget_message(Entity *e) {
    PlayerData *player = &playerWork[e->type];
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        if (localPlayerIndex != e->type) {
            return;
        }
    }
    if (data_021348fc & (1 << player->unk_1c)) {
        return;
    }
    data_021348fc |= 1 << player->unk_1c;
    MessageRequest(data_02115ae0[player->unk_1c]);
}
