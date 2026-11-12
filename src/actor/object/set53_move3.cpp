#include "engine/functions.h"
#include "global.h"
#include "actor/object/set53_move3.h"

// set53_move3 (0x020713a0): the boat hull moving on the water. Pushes the players aside, moves one pixel step at a
// time through the current, turns on the flow cells, stops at the landing cells and places the jetty pieces around it.

// Map cell column and row of a position
static inline int Set53_CellX(s16 x) {
    return (x - mapState.originX) >> 4;
}
static inline int Set53_CellY(s16 y) {
    return (y - mapState.originY) >> 4;
}

void set53_move3(Entity *e) {
    Vars_Set53Hull *v = VARS(Vars_Set53Hull, e);
    u16 *bg;
    u8 i;
    PlayerData *player;
    BOOL drifted;
    u8 steps;
    u16 cell;
    int kind;
    Entity *piece;
    s16 dx;
    s16 dy;

    bg = (u16 *)GetBgBuffAdrs(e->layer);
    drifted = FALSE;
    player = playerWork;
    for (i = 0; i < 4 && player->entity != NULL; i++, player++) {
        if (!(player->unk_02 & 0x80) && !(player->statusFlags & 0x1000)) {
            func_02085e08(e, player->entity);
        }
    }
    v->distance += v->speed;
    if (v->speed != 0) {
        e->speed = 0x100;
        for (steps = (v->speed >> 8) + 1; steps != 0; steps--) {
            e->direction = e->animationState << 2;
            if (steps - 1 == 0) {
                e->speed = v->speed & 0xff;
            }
            if (v->cell & 0x4000) {
                bg[(Set53_CellX(e->x.HALF.HI) | (Set53_CellY(e->y.HALF.HI) << 6)) + 2] = v->cell;
                v->cell = 0;
            }
            MoveDir(e);
            cell = func_02083c84(e);
            if (cell == v->cell) {
                continue;
            }
            v->cell = cell;
            switch (cell) {
            case 0x4016:
            case 0x4017:
                bg[(((e->x.HALF.HI - mapState.originX) >> 4) | (((e->y.HALF.HI - mapState.originY) >> 4) << 6)) + 2] =
                    0x4019;
                continue;
            }
            kind = func_02083cdc(e);
            if (kind == 0x2e) {
                drifted = TRUE;
            }
            switch (kind) {
            case 0x2f:
            case 0x36:
            case 0x37:
                if (e->animationState == 0 || e->animationState == 4) {
                    break;
                }
                if (e->animationState & 2) {
                    e->animationState = (e->animationState + 1) & 7;
                } else {
                    e->animationState = (e->animationState - 1) & 7;
                }
                break;
            case 0x30:
            case 0x38:
            case 0x39:
                if (e->animationState == 6 || e->animationState == 2) {
                    break;
                }
                if (e->animationState & 2) {
                    e->animationState = (e->animationState - 1) & 7;
                } else {
                    e->animationState = (e->animationState + 1) & 7;
                }
                break;
            case 0x31:
                if (e->animationState == 0) {
                    e->animationState = 1;
                } else {
                    e->animationState = 5;
                }
                break;
            case 0x32:
                if (e->animationState == 2) {
                    e->animationState = 1;
                } else {
                    e->animationState = 5;
                }
                break;
            case 0x33:
                if (e->animationState == 4) {
                    e->animationState = 3;
                } else {
                    e->animationState = 7;
                }
                break;
            case 0x34:
                if (e->animationState == 0) {
                    e->animationState = 7;
                } else {
                    e->animationState = 3;
                }
                break;
            case 0x2e:
                v->savedDirection = e->animationState ^= 4;
                e->timer = e->subtimer = 0xff;
                e->action = 1;
                v->speed = 0;
                v->savedX = e->x.HALF.HI;
                v->savedY = e->y.HALF.HI;
                EnqueueSFX(0x5a);
                break;
            case 0x35:
            case 0x5e:
            case 0x60:
            case 0x62:
            case 0x64:
                break;
            default:
                switch (func_02083cdc(e)) {
                case 0x43:
                    e->action = 5;
                    InitAnimationForceUpdate(e, 8);
                    playerWork[VARS(Vars_Set53Seat, e->child)->rider0->type].state = 3;
                    playerWork[VARS(Vars_Set53Seat, e->child)->rider1->type].state = 3;
                    FormationBreak();
                    return;
                case 0x21:
                    e->action = 5;
                    InitAnimationForceUpdate(e, 8);
                    playerWork[VARS(Vars_Set53Seat, e->child)->rider0->type].state = 0x11;
                    playerWork[VARS(Vars_Set53Seat, e->child)->rider1->type].state = 0x11;
                    FormationBreak();
                    return;
                default:
                    e->x.HALF.HI = v->savedX;
                    e->y.HALF.HI = v->savedY;
                    e->animationState = v->savedDirection;
                    v->distance = 0;
                    return;
                }
            }
        }
    }
    if (!(e->animationState & 1)) {
        piece = NULL;
        switch ((u8)func_02083ccc(e, data_020db854[e->animationState], data_020db854[e->animationState + 1])) {
        case 0x5d:
            if (!drifted) {
                piece = GetSetWork(0x54, 0, 0);
            }
            break;
        case 0x5f:
            if (!drifted) {
                piece = GetSetWork(0x54, 2, 0);
            }
            break;
        case 0x63:
            if (!drifted) {
                piece = GetSetWork(0x54, 1, 0);
            }
            break;
        case 0x61:
            if (!drifted) {
                piece = GetSetWork(0x54, 3, 0);
            }
            break;
        }
        if (piece != NULL) {
            piece->x.HALF.HI = e->x.HALF.HI + data_020db854[e->animationState];
            piece->y.HALF.HI = e->y.HALF.HI + data_020db854[e->animationState + 1];
        }
        dx = data_020db854[e->animationState ^ 4];
        dy = data_020db854[(e->animationState ^ 4) + 1];
        switch ((u8)func_02083ccc(e, dx, dy)) {
        case 0x5e:
            piece = GetSetWork(0x54, 4, 0);
            if (piece != NULL) {
                piece->x.HALF.HI = e->x.HALF.HI + dx;
                piece->y.HALF.HI = e->y.HALF.HI + dy;
            }
            break;
        case 0x60:
            piece = GetSetWork(0x54, 6, 0);
            if (piece != NULL) {
                piece->x.HALF.HI = e->x.HALF.HI + dx;
                piece->y.HALF.HI = e->y.HALF.HI + dy;
            }
            break;
        case 0x64:
            piece = GetSetWork(0x54, 5, 0);
            if (piece != NULL) {
                piece->x.HALF.HI = e->x.HALF.HI + dx;
                piece->y.HALF.HI = e->y.HALF.HI + dy;
            }
            break;
        case 0x62:
            piece = GetSetWork(0x54, 7, 0);
            if (piece != NULL) {
                piece->x.HALF.HI = e->x.HALF.HI + dx;
                piece->y.HALF.HI = e->y.HALF.HI + dy;
            }
            break;
        }
    }
    if (e->animationState & 0xfb) {
        e->hitbox = data_020db85c;
    } else {
        e->hitbox = data_020db864;
    }
    if (!(e->animationState & 1)) {
        if (e->animationState & 2) {
            e->y.HALF.HI = (e->y.HALF.HI & 0xfff0) + 8;
        } else {
            e->x.HALF.HI = (e->x.HALF.HI & 0xfff0) + 8;
        }
    }
    if (v->speed != 0) {
        v->speed -= 0x20;
        if ((s32)v->speed < 0) {
            v->speed = 0;
        }
    }
    if (e->unk_23 != e->animationState) {
        InitAnimationForceUpdate(e, e->animationState);
    }
    if (v->distance >= 0x2000) {
        EnqueueSFX(0x72);
        v->distance = 0;
    }
    set53_nop(e);
}
