#include "engine/functions.h"
#include "actor/enemy/em2f.h"
#include "global.h"

// nextSet (0x02037f6c, module em2f): counts how often each of the last three attacks (2 bit entries of attackSeed)
// was used, picks the attack that was not used yet (random when all were), starts it and records it in the history.
void nextSet(Entity *e) {
    u8 useCounts[4];
    u8 history;
    u8 attack;

    useCounts[0] = useCounts[1] = useCounts[2] = useCounts[3] = 0;
    history = V(e)->attackSeed;
    attack = 0;
    useCounts[history & 3]++;
    useCounts[(history >> 2) & 3]++;
    useCounts[(history >> 4) & 3]++;
    if (useCounts[1] == 0) {
        attack = 0;
    } else if (useCounts[2] == 0) {
        attack = 1;
    } else if (useCounts[3] == 0) {
        attack = 2;
    } else {
        attack = Random() % 3;
    }
    switch (attack) {
    case 0:
        e->action = 0xe;
        InitAnimationForceUpdate(e, 1);
        EnqueueSFX(0xb2);
        break;
    case 1:
        e->action = 0x17;
        e->timer = 0x3c;
        break;
    case 2:
        e->action = 0x1e;
        e->timer = 0x3c;
        break;
    }
    V(e)->attackSeed = (V(e)->attackSeed << 2) | (attack + 1);
    e->subtimer = 3;
}
