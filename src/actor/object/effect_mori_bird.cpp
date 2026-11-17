#include "engine/functions.h"
#include "global.h"
#include "actor/object/effect_mori.h"

// Bird spawn of the forest effect (module effect_mori). Address -> name:
//   0x0206dcc8 birdSet (original name)

// The spawn table is read through a non-const view here: a const declaration lets mwcc hoist the record loads above
// the stores into the bird.
extern BirdRecord data_02116104[]; // birdRecords

// Spawns one bird from a random record of the table and turns its heading by a random step of -2..+2.
void birdSet(Entity *e) {
    BirdRecord *record = &data_02116104[Random() & 3];
    Entity *bird = GetSetWork(0x46, 0xb, e->type2);

    if (bird == NULL) {
        return;
    }
    bird->x.HALF.HI = record->x;
    bird->y.HALF.HI = record->y;
    bird->direction = record->direction;
    bird->speed = record->speed & 0xff;
    switch (Random() & 0xf) {
    case 0:
        bird->direction += 1;
        break;
    case 1:
        bird->direction -= 1;
        break;
    case 2:
        bird->direction += 2;
        break;
    case 3:
        bird->direction -= 2;
        break;
    }
    bird->direction &= 0x1f;
}
