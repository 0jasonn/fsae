#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "actor/object/set29.h"

extern const u8 set29TypeTable[]; // palette index per type

// set29_init (0x02068bf4): finds the BG cell under the object. In a running game that is not mode 5 or 6, an object
// whose cell test (test) succeeds is removed at once; otherwise the object remembers the cell and its value, picks
// its palette from set29TypeTable and becomes visible.
void set29_init(Entity *e) {
    u16 *cells = (u16 *)GetBgBuffAdrs(e->layer);
    u16 *p;
    u16 index = ((e->x.HALF.HI - mapState.originX) >> 4) | (((e->y.HALF.HI - mapState.originY) >> 4) << 6);
    if (gameState.active == 0 && gameState.unk_01 != 5 && gameState.unk_01 != 6) {
        if (test(e, index, *(cells + *(cells + index + 2) + 0x2802)) != 0) {
            PutObjWork(e);
            return;
        }
    }
    p = cells + 2;
    VARS(Vars_Set29, e)->cellPtr = p + index;
    VARS(Vars_Set29, e)->cellValue = p[index];
    e->spriteSettings.b16 = set29TypeTable[e->type];
    e->action++;
    e->spriteSettings.b0 = 1;
    e->unk_2e = 0;
    e->unk_5e.b0 = 0;
    InitAnimationForceUpdate(e, 0);
}
