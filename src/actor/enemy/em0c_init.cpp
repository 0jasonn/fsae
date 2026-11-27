#include "engine/functions.h"
#include "actor/enemy/em12.h"
#include "game/em0c_3.h"

extern const u8 data_020cfe0c[]; // em0c timer table, indexed by the low nibble of the placed timer byte

// em0c_init(OBJ_WORK_*), 0x0202c5fc: the placed timer byte holds the type (high nibble) and an index into the timer
// table (low nibble); the low six bits of the placed x are the direction and those of the placed y select the entry in
// the area's info table, which gives the spawn cell and the sensor box. The action starts at 1 (type bit 0 set) or 2;
// the subtimer is the timer, plus a random 0..3 when direction bit 5 is set.
void em0c_init(Entity *e) {
    s16 y;
    Em0cSensor *sensor = VARS(Em0cSensor, e);

    sensor->typeBits = ParseTypeBits(e->type);
    sensor->typeBits2 = ParseTypeBits(e->type2);
    e->type = (e->timer >> 4) & 0xf;
    e->timer = data_020cfe0c[e->timer & 0xf];
    e->direction = e->x.HALF.HI & 0x3f;
    y = e->y.HALF.HI;
    const u8 *info = GetInfoAdrs(e->areaIndex, (y >> 6) & 0x3f);
    s32 infoIndex = (e->y.HALF.HI & 0x3f) * 6;
    const u8 *entry = info + infoIndex;
    e->x.HALF.HI = (entry[0] << 4) + 8 + data_0213492c[e->areaIndex * 2];
    e->y.HALF.HI = (entry[1] << 4) + 8 + em12_spawnOffsetY[e->areaIndex * 2];
    func_0208ae30(e);

    sensor->boxX = data_0213492c[e->areaIndex * 2] + (entry[2] << 4);
    sensor->boxY = em12_spawnOffsetY[e->areaIndex * 2] + (entry[3] << 4);
    sensor->boxWidth = (entry[4] << 4) + 0x10;
    sensor->boxHeight = (entry[5] << 4) + 0x10;

    if ((e->type & 1) == 0) {
        e->action = 2;
    } else {
        e->action = 1;
        e->subtimer = e->timer + (Random() & 3);
    }
    if ((e->direction & 0x20) == 0) {
        e->subtimer = e->timer;
    } else {
        e->subtimer = e->timer + (Random() & 3);
    }
}
