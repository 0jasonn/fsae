#include "engine/functions.h"
#include "game/bganm_api.h"
#include "actor/enemy/em0b_init.h"

extern const s16 data_020cfdec[]; // em0b step table: x and y step for each direction / 8

// em0b_move(OBJ_WORK_*), 0x0202c350: the slide of em0b. It turns around (next action, half speed, opposite direction,
// sound when it has already moved) when the cell one step ahead is reserved by a push block, when func_020847a0 fails,
// or, while the timer runs, when the position passes slideLimit in the slide direction. counter78 counts the frames
// moved, up to 0x3c.
void em0b_move(Entity *e) {
    s32 step;
    int index;
    BOOL turn;
    BOOL blocked;

    index = (e->direction >> 3) * 2;
    step = (s16)(e->speed >> 8);
    turn = FALSE;
    // the cell one step ahead (64 cells per row); "blocked = ... : turn" reuses the 0 of turn as in the ROM
    blocked = Check1BlockOshiYoyaku(((e->y.HALF.HI + step * data_020cfdec[index + 1]) >> 4) * 0x40 |
                                        ((e->x.HALF.HI + step * data_020cfdec[index]) >> 4),
                                    e->layer) != 0
                  ? TRUE
                  : turn;
    if (func_020847a0(e) == 0 || blocked) {
        turn = TRUE;
    } else if (e->timer != 0) {
        switch (e->direction >> 3) {
        case 0:
            if (e->y.HALF.HI < VARS(Vars_Em0bInit, e)->slideLimit) {
                turn = TRUE;
            }
            break;
        case 1:
            if (e->x.HALF.HI > VARS(Vars_Em0bInit, e)->slideLimit) {
                turn = TRUE;
            }
            break;
        case 2:
            if (e->y.HALF.HI > VARS(Vars_Em0bInit, e)->slideLimit) {
                turn = TRUE;
            }
            break;
        case 3:
            if (e->x.HALF.HI < VARS(Vars_Em0bInit, e)->slideLimit) {
                turn = TRUE;
            }
            break;
        }
    }
    if (turn) {
        e->action++;
        e->speed >>= 1;
        e->direction ^= 0x10;
        if (VARS(Vars_Em0bInit, e)->counter78 != 0) {
            SoundReq(0x1d);
        }
    }
    if (VARS(Vars_Em0bInit, e)->counter78 < 0x3c) {
        VARS(Vars_Em0bInit, e)->counter78++;
    }
}
