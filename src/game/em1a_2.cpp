// Actor em1a (original names from the debug build): em1a_getNextInfo (second unit; the first is em1a.cpp).
#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em1a.h"

// One route entry: bit 15 of cmd selects a wait of `distance` frames, otherwise cmd holds the direction (bits 2..4 select
// the move) and `distance`/`speed` the length and speed of the leg.
typedef struct Em1aRouteEntry {
    /* 00 */ u16 cmd;
    /* 02 */ u16 distance;
    /* 04 */ u16 speed;
    /* 06 */ u16 unk_06;
} Em1aRouteEntry;

void em1a_getNextInfo(Entity *e) {
    Vars_Em1a *vars = VARS(Vars_Em1a, e);
    Em1aRouteEntry *entry;
    u16 cmd;
    u8 direction;

    if (((Em1aRouteEntry *)vars->infoPtr)->cmd == 0xffff) {
        vars->infoPtr = vars->infoBase;
    }
    entry = (Em1aRouteEntry *)vars->infoPtr;
    cmd = entry->cmd;
    if (cmd & 0x8000) {
        e->subAction = 8;
        e->timer = (u8)entry->distance;
    } else {
        e->direction = (u8)cmd;
        direction = e->subAction = (cmd & 0xff) >> 2;
        switch (direction) {
        case 1:
            vars->targetX = e->x.HALF.HI + entry->distance;
        case 0:
            vars->targetY = e->y.HALF.HI - entry->distance;
            break;
        case 3:
            vars->targetY = e->y.HALF.HI + entry->distance;
        case 2:
            vars->targetX = e->x.HALF.HI + entry->distance;
            break;
        case 5:
            vars->targetX = e->x.HALF.HI - entry->distance;
        case 4:
            vars->targetY = e->y.HALF.HI + entry->distance;
            break;
        case 7:
            vars->targetY = e->y.HALF.HI - entry->distance;
        case 6:
            vars->targetX = e->x.HALF.HI - entry->distance;
            break;
        }
        if (entry->speed != 0) {
            e->speed = entry->speed;
        }
    }
    vars->infoPtr += 8;
}
