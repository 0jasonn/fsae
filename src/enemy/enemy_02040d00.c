#include "enemy/actor_020407c8.h"
#include "global.h"

ARM void BubbleReset(Entity *e) {
    Entity *c = GetEnemyWork(0x26);
    if (c == NULL) {
        return;
    }
    c->x.HALF.HI = V(e)->unk_70;
    c->y.HALF.HI = V(e)->unk_72;
    c->unk_52 = e->unk_52;
    V(c)->unk_74 = V(e)->unk_74;
    V(c)->unk_76 = V(e)->unk_76;
    V(c)->unk_78 = V(e)->unk_78;
    V(c)->unk_7a = V(e)->unk_7a;
    V(c)->unk_7c = 0x258;
    func_0208ae30(c);
}
