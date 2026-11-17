#include "engine/functions.h"
#include "global.h"
#include "actor/object/set09.h"

// set09_init (0x02062bd4): rescales x to 60 pixels per unit (keeping the unit in unk_16), looks up the 8-byte entry
// table of the area for y and registers each entry whose kind (top 3 bits) is 2 or 3 as a random cell set. The
// entry count becomes the timer unless a smaller one was preset; type 0xff skips the wait.
void set09_init(Entity *e) {
    const u16 *info;
    u16 count;
    u16 word;
    u16 kind;
    s16 x = e->x.HALF.HI;
    e->action = 1;
    e->unk_16 = x;
    e->x.HALF.HI = x * 0x3c;
    info = (const u16 *)GetInfoAdrs(e->areaIndex, e->y.HALF.HI);
    VARS(Vars_Set09, e)->info = info;
    count = 0;
    for (word = info[0]; word != 0xffff; word = (info += 4)[0]) {
        kind = (word & 0xe000) >> 13;
        if ((u16)(kind + 0xfffe) <= 1) {
            GetCellsInRandomSet(((info[2] & 0xfc0) >> 6) + (info[3] & 0xfc0), (info[2] & 0x3f) + 1, (info[3] & 0x3f) + 1);
        }
        count++;
    }
    if (e->timer == 0 || count < e->timer) {
        e->timer = count;
    }
    if (e->type == 0xff) {
        e->action++;
        return;
    }
    VARS(Vars_Set09, e)->typeBits = ParseTypeBits(e->type);
}
