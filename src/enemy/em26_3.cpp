#include "engine/functions.h"
#include "enemy/em26.h"
#include "global.h"

ARM void BubbleReset(Entity *e) {
    Entity *bubble = GetEnemyWork(0x26);
    if (bubble == NULL) {
        return;
    }
    bubble->x.HALF.HI = V(e)->homeX;
    bubble->y.HALF.HI = V(e)->homeY;
    bubble->unk_52 = e->unk_52;
    V(bubble)->resetVal0 = V(e)->resetVal0;
    V(bubble)->resetVal1 = V(e)->resetVal1;
    V(bubble)->resetVal2 = V(e)->resetVal2;
    V(bubble)->resetVal3 = V(e)->resetVal3;
    V(bubble)->resetTimer = 0x258;
    func_0208ae30(bubble);
}
