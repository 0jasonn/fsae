#include "engine/functions.h"
#include "global.h"

// honyaMove (0x02043428) and honyaGetInfo (0x02043520): the "honya" script movement of the encounter enemies. The script
// is a list of u16 records (command, arguments; 0xffff in an optional argument keeps the current value, 0xffff as the
// command ends the script). honyaGetInfo reads the next command into the actor's move state, honyaMove runs it:
//   command 0: move straight for `timer` frames (args: frames, speed, direction)
//   command 1: move for `timer` frames, then turn by turnStep direction units and repeat repeatCount times
//              (args: frames, speed, turn step, repeat count)
//   command 2: jump (z velocity = lo + (hi << 16)) until it lands at z -2 (args: lo, hi, speed, direction)
//   command 3: wait for `timer` frames (arg: frames)


// Move state at the end of the entity
typedef struct HonyaVars {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ const u16 *script;
    /* 74 */ u8 mode;
    /* 75 */ s8 turnStep;
    /* 76 */ u8 repeatCount;
    /* 77 */ u8 unk_77;
    /* 78 */ u16 timer;
    /* 7a */ u16 reload;
} HonyaVars;

void honyaMove(Entity *e) {
    HonyaVars *v = VARS(HonyaVars, e);
    switch (v->mode) {
        case 0:
            MoveDir(e);
            v->timer--;
            if (v->timer == 0) {
                honyaGetInfo(e);
            }
            break;
        case 1:
            MoveDir(e);
            v->timer--;
            if (v->timer == 0) {
                v->timer = v->reload;
                e->direction = (e->direction + v->turnStep) & 0x1f;
                v->repeatCount--;
                if (v->repeatCount == 0) {
                    honyaGetInfo(e);
                }
            }
            break;
        case 2:
            MoveDir(e);
            UpdateGravity(e, 0x2000);
            if (e->z.HALF.HI >= -2) {
                e->z.HALF.HI = -2;
                honyaGetInfo(e);
            }
            break;
        case 3:
            v->timer--;
            if (v->timer == 0) {
                honyaGetInfo(e);
            }
            break;
    }
}

void honyaGetInfo(Entity *e) {
    HonyaVars *v = VARS(HonyaVars, e);
    const u16 *script = v->script;
    const u16 *next;
    if (script[0] == 0xffff) {
        return;
    }
    v->mode = script[0];
    next = script + 1;
    switch (script[0]) {
        case 0:
            v->timer = script[1];
            if (script[2] != 0xffff) {
                e->speed = script[2];
            }
            if (next[2] != 0xffff) {
                e->direction = next[2];
            }
            next += 3;
            break;
        case 1: {
            v->reload = script[1];
            if (script[2] != 0xffff) {
                e->speed = script[2];
            }
            v->turnStep = next[2];
            v->repeatCount = next[3];
            e->direction = (e->direction + v->turnStep) & 0x1f;
            v->timer = v->reload;
            goto advance4;
        }
        case 2:
            e->zVelocity = script[1] + (script[2] << 16);
            if (script[3] != 0xffff) {
                e->speed = script[3];
            }
            if (next[3] != 0xffff) {
                e->direction = next[3];
            }
advance4:
            next += 4;
            break;
        case 3:
            v->timer = script[1];
            next = script + 2;
            break;
    }
    v->script = next;
}
