#include "engine/functions.h"
#include "global.h"
#include "game/shikake.h"
#include "game/shikake_api.h"

// Switch-block helpers (module shikake). Original names from the debug build.
//   ShikakeMove

// Runs the big-block and other-kind handlers over the 8-byte records of data_02134bb0, then clears both counts.
void ShikakeMove(void) {
    u16 i;
    u8 *record;

    record = data_02134bb0;
    for (i = 0; i < (s32)data_021348e4; i++, record += 8) {
        switch (*(u32 *)record >> 24) {
        case 1:
            shikake_bigblock((u32 *)record);
            break;
        case 2:
            func_020227b4((u32 *)record);
            break;
        }
    }
    data_021348e4 = 0;
    data_021348f0 = 0;
}

// Request check of the switch-block records: a request in state 1 is refused (returns 0) while another record of the same
// key and type exists; any other state is always accepted.
BOOL shikake_req_check(SHIKAKEWORK *req) {
    SHIKAKEWORK *record;
    u8 i;

    if (1 != req->state) {
        return 1;
    }
    record = data_02134e70;
    for (i = 0; i < data_021348f0; i++, record++) {
        if (req->key == record->key && req->unk_00 != record->unk_00 && req->type == record->type) {
            return 0;
        }
    }
    return 1;
}

// Switch-block helpers (module shikake), second unit. Original names from the debug build.
//   shikake_playercheck

// Returns 0 as soon as one of the four attached objects of kind 1 fails func_020860dc; 1 otherwise.
BOOL shikake_playercheck(SHIKAKEWORK *req) {
    u8 i;
    Entity *obj;

    for (i = 0; i < 4; i++) {
        obj = req->objs[i];
        if (obj != NULL && obj->objKind == 1) {
            if (func_020860dc(obj) == 0) {
                return 0;
            }
        }
    }
    return 1;
}
