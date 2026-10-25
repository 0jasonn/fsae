#include "engine/functions.h"
#include "global.h"
#include "enemy/em21.h"

// Functions in this file: Em21 (0x0203f1d0), em21_normal (0x0203f1f8), em21_knockback (0x0203f214, was em21_knockback).

ARM void Em21(Entity *e) {
    em21_stateTable[func_02084a30(e)](e);
}

ARM void em21_normal(Entity *e) {
    em21_actionTable[e->action](e);
}

ARM void em21_knockback(Entity *e) {
    GenericKnockback(e, em21_stateTable);
}
