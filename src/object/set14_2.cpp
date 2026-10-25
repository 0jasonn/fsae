#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/heart_lift.h"
#include "object/set14_2.h"

// Set14 actor, second unit (module set14). Address -> name:
//   0x02064964 set14_move (original name set14_move(OBJ_WORK_*))
//   0x02064a20 plkaiten (parked in scratch/agentC/nonmatching, not matching yet)

typedef struct Vars_Set14Move {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u8 turnState[4]; // per rider type: state of the turn along the path, read by plkaiten
    /* 7c */ u8 prevFrame;    // copy of the frame taken at the start of each move
    /* 7d */ u8 turnMask;     // bit per rider type: that rider is being turned
} Vars_Set14Move;

ARM void set14_move(Entity *e) {
    u8 result;

    VARS(Vars_Set14Move, e)->prevFrame = e->frame;
    UpdateAnimationSingleFrame(e);
    result = 0;
    if ((data_0212ceb0[0].unk_0d[2] & 3) == 3) {
        result |= plkaiten(e, data_0212ceb0[0].entity);
    }
    if ((data_0212ceb0[1].unk_0d[2] & 3) == 3) {
        result |= plkaiten(e, data_0212ceb0[1].entity);
    }
    if ((data_0212ceb0[2].unk_0d[2] & 3) == 3) {
        result |= plkaiten(e, data_0212ceb0[2].entity);
    }
    if ((data_0212ceb0[3].unk_0d[2] & 3) == 3) {
        result |= plkaiten(e, data_0212ceb0[3].entity);
    }
    VARS(Vars_Set14Move, e)->turnMask &= result;
}
