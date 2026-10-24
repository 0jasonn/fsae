#include "engine/functions.h"
#include "global.h"
#include "game/knife_comm_icon.h"

// Knife::Comm::WirelessIcon, 0x0209a660 to 0x0209a6cc: deleting dtor, initialize_16x16_ColorMode and finalize.
// updateObj (0x0209a6cc) is parked. The functions stay plain extern "C" because twl.cpp refers to initialize by plain name.

// WirelessIcon::~WirelessIcon, deleting dtor (0x0209a660): frees the block and returns it.
extern "C" WirelessIcon *Knife_Comm_WirelessIcon_dtor_WirelessIcon(WirelessIcon *self);
ARM WirelessIcon *Knife_Comm_WirelessIcon_dtor_WirelessIcon(WirelessIcon *self) {
    operator delete(self);
    return self;
}

extern "C" void Knife_Comm_WirelessIcon_finalize(WirelessIcon *self);

// WirelessIcon::initialize_16x16_ColorMode(ColorType, int) (0x0209a674)
extern "C" void Knife_Comm_WirelessIcon_initialize_16x16_ColorMode(WirelessIcon *self, u32 colorType, s32 paletteNo);
ARM void Knife_Comm_WirelessIcon_initialize_16x16_ColorMode(WirelessIcon *self, u32 colorType, s32 paletteNo) {
    Knife_Comm_WirelessIcon_finalize(self);
    self->unk_05 = 0;
    self->unk_06 = 0;
    self->paletteNo = paletteNo;
    self->colorType = colorType;
    self->enabled = 1;
}

// WirelessIcon::finalize() (0x0209a6a8): clears the state fields.
extern "C" void Knife_Comm_WirelessIcon_finalize(WirelessIcon *self);
ARM void Knife_Comm_WirelessIcon_finalize(WirelessIcon *self) {
    self->enabled = 0;
    self->unk_05 = 0;
    self->unk_06 = 0;
    self->paletteNo = 0;
    self->charNo = 0;
    self->unk_0c = 0;
    self->unk_14 = 0;
}
