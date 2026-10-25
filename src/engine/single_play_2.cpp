#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/single_play_d.h"

// Knife::Single::SinglePlay initializers and the warp info setter, 0x02099cec to 0x02099da8. The log list is the C++
// member SinglePlayLogList::Initialize at 0x0209a060 (mangled in symbols.txt).

extern u8 data_0212ceb0[]; // PL_WORK array of the players (bss); the controlled player's fields 0x30 and 0xc4 are cleared

// SinglePlay::InitializeFormation() (0x02099cec): clears the formation state and initializes the log list
extern "C" void Knife_Single_SinglePlay_InitializeFormation(void *self);
ARM void Knife_Single_SinglePlay_InitializeFormation(void *self) {
    SinglePlayWork *sp;

    sp = (SinglePlayWork *)self;
    sp->unk_0a = 0;
    sp->unk_28 = 0;
    sp->unk_26 = 0;
    sp->unk_24 = 0;
    sp->unk_0c = 0;
    sp->unk_0b = 0;
    sp->unk_20 = 0xffff;
    sp->unk_0f = 0;
    ((Knife::Single::SinglePlay::SinglePlayLogList *)sp->unk_34)->Initialize();
}

// SinglePlay::InitializeCont() (0x02099d28): clears the controller state, the log list and the player fields
extern "C" void Knife_Single_SinglePlay_InitializeCont(void *self);
ARM void Knife_Single_SinglePlay_InitializeCont(void *self) {
    SinglePlayWork *sp;

    sp = (SinglePlayWork *)self;
    sp->formationChanging = 0;
    sp->unk_0b = 0;
    sp->unk_0a = 0;
    sp->unk_28 = 0;
    sp->unk_26 = 0;
    sp->unk_24 = 0;
    sp->unk_20 = 0xffff;
    sp->unk_0f = 0;
    ((Knife::Single::SinglePlay::SinglePlayLogList *)sp->unk_34)->Initialize();
    data_0212ceb0[0x30] = 0;
    data_0212ceb0[0xc4] = 0;
    sp->unk_2e = 0;
    sp->unk_2c = 0;
    sp->unk_30 = NULL;
    sp->unk_12 = 0;
}

// SinglePlay::SetWarpInfo(unsigned char, unsigned char) (0x02099d88): stores the pair when none is set yet or the
// player bit of the controller matches the first value
extern "C" void Knife_Single_SinglePlay_SetWarpInfo(void *self, u8 first, u8 second);
ARM void Knife_Single_SinglePlay_SetWarpInfo(void *self, u8 first, u8 second) {
    SinglePlayWork *sp;

    sp = (SinglePlayWork *)self;
    if (sp->unk_08 == 0 || first == (1 << sp->contNo)) {
        sp->unk_08 = first;
        sp->unk_09 = second;
    }
}
