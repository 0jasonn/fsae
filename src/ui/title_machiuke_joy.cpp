#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

extern u8 comWork[];
extern u16 playerKeys[];
extern u16 data_0212c514;

// title_machiuke_joy (0x02052a80): per-frame key update of the waiting screen. For each of the four players it takes
// the key word from the exchange work (stride 0x34, 0xffff = no data), derives the newly pressed keys against the
// previous frame and remembers the word. Without a wireless session player 0's key word comes from data_0212c514.
void title_machiuke_joy(void) {
    void *app;
    u16 i;
    func_020909c8();
    app = KnifeApp_getInstance();
    for (i = 0; i < 4; i++) {
        u16 key = *(u16 *)(comWork + i * 0x34 + 0x7a);
        if (key != 0xffff) {
            playerKeys[i] = key & ~playerKeysPrev[i];
        } else {
            playerKeys[i] = 0;
        }
        playerKeysPrev[i] = key;
    }
    if (KnifeApp_isWirelessMode(app) == 0) {
        playerKeys[0] = data_0212c514;
        *(u16 *)(comWork + 0x7a) = data_0212c514;
    }
    *(u16 *)(comWork + 0x12) = data_0212c514;
}
