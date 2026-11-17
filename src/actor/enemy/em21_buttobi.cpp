#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em21_buttobi.h"

// Functions in this file: em21_buttobi (0x0203f228).

// Runs the knock-back move with the base direction and a fixed speed, then restores both.
void em21_buttobi(Entity *e) {
    u16 savedSpeed;
    u8 savedDirection;

    if ((s8)e->unk_42 > 0) {
        e->unk_42--;
    } else {
        e->unk_42++;
    }
    savedDirection = e->direction;
    savedSpeed = e->speed;
    e->speed = 0x280;
    e->direction = e->baseDirection;
    func_02084828(e);
    e->speed = savedSpeed;
    e->direction = savedDirection;
}
