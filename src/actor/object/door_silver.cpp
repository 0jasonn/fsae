#include "engine/functions.h"
#include "global.h"
#include "actor/object/door_silver.h"

extern DoorSilverBlock data_0212c75c;
extern u8 data_021349c0[];
extern s16 data_02115c78[][3];
extern EntityFunc set31TypeTable[];
extern EntityFunc doorSilverTable[];

void Set31(Entity *e) {
    set31TypeTable[e->type](e);
}

void door_silver(Entity *e) {
    doorSilverTable[e->action](e);
}
