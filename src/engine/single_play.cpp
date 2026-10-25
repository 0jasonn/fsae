#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/single_play_d.h"

// Knife::Single::SinglePlay controller and formation requests, 0x02099550 to 0x02099704. The object is the SinglePlay
// singleton (SinglePlayWork in single_play_d.h); the members are plain names, so they are extern "C" taking self.

extern u16 data_0212c510; // key mask (bss)
extern u16 data_0212c514; // key state (bss)

extern "C" void Knife_Single_SinglePlay_InitializeCont(void *self);
extern "C" void Knife_Single_SinglePlay_InitializeFormation(void *self);

// SinglePlay::SetContNo(unsigned char) (0x02099550): requests a controller change unless it is the current one
extern "C" void Knife_Single_SinglePlay_SetContNo(void *self, u8 no);
ARM void Knife_Single_SinglePlay_SetContNo(void *self, u8 no) {
    SinglePlayWork *sp;

    sp = (SinglePlayWork *)self;
    if (sp->contNo != no || sp->contChanging != 0) {
        sp->reqKind = 1;
        sp->reqNo = no;
    }
}

// SinglePlay::SetContNoDirect(unsigned char) (0x02099570): changes the controller now
extern "C" void Knife_Single_SinglePlay_SetContNoDirect(void *self, u8 no);
ARM void Knife_Single_SinglePlay_SetContNoDirect(void *self, u8 no) {
    SinglePlayWork *sp;

    u8 changing;

    sp = (SinglePlayWork *)self;
    if (sp->contNo != no) {
        sp->flags07 = sp->flags07 | 1;
        sp->unk_1a = (data_0212c514 & ~data_0212c510) & 0x803;
    }
    changing = sp->contChanging;
    sp->contNo = no;
    if (changing != 0) {
        sp->flags07 = sp->flags07 | 2;
    }
    sp->contChanging = 0;
    Knife_Single_SinglePlay_InitializeCont(self);
}

// SinglePlay::ChangeContPlayer() (0x020995e4): requests the next controller
extern "C" void Knife_Single_SinglePlay_ChangeContPlayer(void *self);
ARM void Knife_Single_SinglePlay_ChangeContPlayer(void *self) {
    SinglePlayWork *sp;

    sp = (SinglePlayWork *)self;
    sp->reqKind = 1;
    sp->reqNo = 0xff;
}

// SinglePlay::ChangeContPlayerDirect() (0x020995f8): plays the sound and changes to the other controller now
extern "C" void Knife_Single_SinglePlay_ChangeContPlayerDirect(void *self);
ARM void Knife_Single_SinglePlay_ChangeContPlayerDirect(void *self) {
    SinglePlayWork *sp;

    sp = (SinglePlayWork *)self;
    SoundReq(0xc5);
    Knife_Single_SinglePlay_SetContNoDirect(self, (sp->contNo + 1) & 1);
}

// SinglePlay::SetFormationNo(unsigned char) (0x02099620, no original name): requests a formation change
extern "C" void Knife_Single_SinglePlay_SetFormationNo(void *self, u8 no);
ARM void Knife_Single_SinglePlay_SetFormationNo(void *self, u8 no) {
    SinglePlayWork *sp;

    sp = (SinglePlayWork *)self;
    sp->reqKind = 2;
    sp->reqNo = no;
}

// SinglePlay::SetFormationNoDirect(FORMATION_NO) (0x02099630): changes the formation now
extern "C" void Knife_Single_SinglePlay_SetFormationNoDirect(void *self, u8 no);
ARM void Knife_Single_SinglePlay_SetFormationNoDirect(void *self, u8 no) {
    SinglePlayWork *sp;

    sp = (SinglePlayWork *)self;
    if (no != 0) {
        sp->formationChanging = 1;
        if (sp->contChanging == 0) {
            sp->flags07 = sp->flags07 | 4;
        }
    } else {
        sp->formationChanging = 0;
        if (sp->contChanging != 0) {
            SoundReq(0xc5);
            sp->flags07 = sp->flags07 | 2;
        }
    }
    sp->contChanging = no;
    Knife_Single_SinglePlay_InitializeFormation(self);
}

// SinglePlay::ChangeFormationNo() (0x02099694): requests the next formation
extern "C" void Knife_Single_SinglePlay_ChangeFormationNo(void *self);
ARM void Knife_Single_SinglePlay_ChangeFormationNo(void *self) {
    SinglePlayWork *sp;

    sp = (SinglePlayWork *)self;
    sp->reqKind = 2;
    sp->reqNo = 0xff;
}
