#include "engine/functions.h"
#include "global.h"
#include "object/objdecls_a.h"

extern u8 data_021349c0[];
void key_pos_set(Entity *e);
typedef struct Vars_Key {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u8 posIndex;
} Vars_Key;

// key_move, 0x02069930
ARM void key_move(Entity *e) {
    Vars_Key *v = VARS(Vars_Key, e);
    if (data_021349c0[8] >= 2) {
        SoundReq(0x200);
        PutObjWork(e);
        return;
    }
    if (e->timer != 0) {
        e->timer--;
        if (e->type2 == 0) {
            SoundReq(0x7e);
        }
        return;
    }
    v->posIndex += data_021349c0[10];
    key_pos_set(e);
}
