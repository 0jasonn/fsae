#include "engine/functions.h"
#include "knife/comm/singleplay_init.h"
#include "knife/comm/singleplay.h"

// Knife::Single::SinglePlay::GetInstance() (0x02093b5c): the first call builds the static instance (data_02178df4): its
// log list (data_02178e28) first, then Initialize, registers its destructor and sets the done bit (bit 0 of the flags word
// at +4 of the guard object data_02178de0).

extern "C" {
void Chain_Push(void *obj, void *dtor, void *handle);
void *Knife_Single_SinglePlay_SinglePlayLogList_SinglePlayLogList(void *self);
}

typedef struct StaticGuard {
    u32 unk_00;
    u32 flags;
} StaticGuard;

extern StaticGuard data_02178de0;
extern u8 data_02178de8[];
extern u8 data_02178df4[];
extern u8 data_02178e28[];

u8 *Knife_Single_SinglePlay_GetInstance(void) {
    u8 *instance;

    if ((data_02178de0.flags & 1) == 0) {
        Knife_Single_SinglePlay_SinglePlayLogList_SinglePlayLogList(data_02178e28);
        instance = data_02178df4;
        ((void (*)(void *))Knife_Single_SinglePlay_Initialize)(instance);
        Chain_Push(instance, (void *)Knife_Single_SinglePlay_dtor_SinglePlay, data_02178de8);
        data_02178de0.flags |= 1;
    }
    return data_02178df4;
}
