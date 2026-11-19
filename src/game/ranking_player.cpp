#include "engine/functions.h"
#include "engine/player.h"
#include "game/ranking_player.h"
#include "global.h"

// ranking_player_set (0x02055194): puts the demo Link of every player on the ranking floor row (y 0x1d8) and
// spaces them by player count; each gets a colour (palette 0xc + index) and the local player becomes the camera
// target. Then the walk animation and the two set objects (type 0xd, kinds 0 and 2) of the player are created.
void ranking_player_set(void) {
    u8 i;
    Entity *link;
    for (i = 0; i < gameState.playerCount; i++) {
        link = func_02072554(i);
        link->spriteSettings.b0 = 1;
        link->y.HALF.HI = 0x1d8;
        switch (gameState.playerCount) {
            case 2:
                link->x.HALF.HI = (((i + 1) * 10) << 3) + 8;
                break;
            case 3:
                link->x.HALF.HI = ((i * 5 + 10) << 3) + 8;
                break;
            case 4:
                link->x.HALF.HI = ((i * 5 + 7) << 3) + 12;
                break;
        }
        link->spriteSettings.b16 = i + 0xc;
        link->spriteSettings.b20 = link->spriteSettings.b16;
        if (i == localPlayerIndex) {
            mapState.target = link;
        }
        DemoLinkWalkSet(i, 0xff, 0);
        GetSetWork(0xd, 0, i);
        GetSetWork(0xd, 2, i);
    }
}
