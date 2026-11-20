#include "engine/functions.h"
#include "engine/player.h"

// BindPlayer(playerNo) (0x02054788): puts one player into the bound state: sets the flag byte (bit 7), the three
// bind-state bytes and byte 0x27, and gives the player entity the maximum invincibility (iframes 0xfe).
void BindPlayer(u8 index) {
    playerWork[index].unk_07 = 0x80;
    playerWork[index].unk_27 = playerWork[index].unk_0a = playerWork[index].unk_0b = playerWork[index].unk_1a = 1;
    playerWork[index].entity->iframes = 0xfe;
}
