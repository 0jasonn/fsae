#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/decls_b2.h"
#include "game/doorsel_appear.h"

// doorsel_appear (0x0202abfc): steps 0, 1 and 2 of the door select appear sequence. Step 0 sets up the sprite of
// every player (position from data_020f260c), then sets the timer in effectState and advances the step; step 1 walks
// each link to its door; step 2 counts the timer down and then picks the next door select step from the number of
// entries.
void doorsel_appear(void) {
    u8 i;

    switch (data_0212c4dc) {
    case 0:
        for (i = 0; i < gameState.playerCount; i++) {
            s16 *pos = GetTablePlNum(data_020f260c, i);
            Entity *sprite = func_02072554(i);
            sprite->spriteSettings.b0 = 2;
            sprite->x.HALF.HI = pos[0] + 8;
            sprite->y.HALF.HI = pos[1] + 0x10;
            sprite->animationState = 0;
            sprite->unk_2e = 3;
            sprite->unk_5e.b2 = 1;
            sprite->unk_20 = (i << 5) + 0x80;
            sprite->spriteSettings.b14 = 0;
            sprite->spriteSettings.b30 = 0;
            sprite->spriteSettings.b6 = 2;
        }
        data_0212c4dc++;
        effectState.timer = 0x40;
        break;
    case 1:
        for (i = 0; i < gameState.playerCount; i++) {
            DemoLinkWalkSet(i, 0x40, 0);
        }
        data_0212c4dc++;
        break;
    case 2:
        effectState.timer--;
        if (effectState.timer != 0) {
            return;
        }
        data_0212c4dc = 0;
        switch (effectState.entryCount) {
        default:
        case 1:
            keyClear();
            data_0212c500 = 5;
            break;
        case 2:
            keyClear();
            data_0212c500 = 4;
            break;
        case 3:
            data_0212c500 = 3;
            break;
        }
        break;
    }
}
