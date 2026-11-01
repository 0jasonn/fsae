#include "engine/functions.h"
#include "engine/player.h"
#include "game/knife_message.h"
#include "global.h"
#include "types.h"

// Functions in this file (module wiz, the Wizzrobe target choice):
//   WizGetTarget (0x0203ca40)

extern const u8 data_020d2400[]; // three rows of eight choices (one row per player count), indexed by (count - 1) * 8

// WizGetTarget(OBJ_WORK_*): sorts the players by health (bubble passes depending on the player count), picks one of
// them with a random choice, falls back to the aim player when it is dead or flagged, and turns the actor towards it.
ARM void WizGetTarget(Entity *e) {
    Entity *a;
    Entity *b;
    Entity *c;
    Entity *d;
    Entity *swap;
    u8 choice;

    a = data_0212ceb0[0].entity;
    b = data_0212ceb0[1].entity;
    c = data_0212ceb0[2].entity;
    d = data_0212ceb0[3].entity;
    if (data_0212c7c8.unk_0 == 2) {
        goto pass1;
    }
    if (data_0212c7c8.unk_0 == 3) {
        goto pass2;
    }
    if (data_0212c7c8.unk_0 != 4) {
        goto choose;
    }
    if (a->health > b->health) { swap = a; a = b; b = swap; }
    if (b->health > c->health) { swap = b; b = c; c = swap; }
    if (c->health > d->health) { swap = c; c = d; d = swap; }
pass2:
    if (a->health > b->health) { swap = a; a = b; b = swap; }
    if (b->health > c->health) { swap = b; b = c; c = swap; }
pass1:
    if (a->health > b->health) { swap = a; a = b; b = swap; }
choose:
    choice = data_020d2400[(data_0212c7c8.unk_0 - 1) * 8 + (Random() & 7)];
    if (choice == 1) {
        goto pickB;
    }
    if (choice == 2) {
        goto pickC;
    }
    if (choice != 3) {
        e->child = a;
    } else {
        e->child = d;
    }
    goto checkChild;
pickB:
    e->child = b;
    goto checkChild;
pickC:
    e->child = c;
checkChild:
    if (e->child->health == 0 || (data_0212c584[e->child->type] & 0x1000) != 0) {
        e->child = EmGetAimPl();
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        e->child = data_0212ceb0[Knife_Single_SinglePlay_GetInstance()[0]].entity;
    }
    e->direction = (GetFacingDirection(e, e->child) + 4) & 0x18;
}
