#include "engine/functions.h"
#include "global.h"
#include "game/knife_comm_icon.h"

// Knife::Comm::ChildInfo, 0x0209a818 to 0x0209a890: setup and cleanup.

// ChildInfo::setup(unsigned short, unsigned char const*, unsigned char const*) (0x0209a818)
extern "C" void Knife_Comm_ChildInfo_setup(ChildInfo *self, u16 id, const u8 *src1, const u8 *src2);
ARM void Knife_Comm_ChildInfo_setup(ChildInfo *self, u16 id, const u8 *src1, const u8 *src2) {
    self->id = id;
    self->flag04 = 0;
    MI_CpuCopy8(src1, self->bytes05, 6);
    MI_CpuCopy8(src2, self->bytes0e, 0x18);
}

// ChildInfo::cleanup() (0x0209a854)
extern "C" void Knife_Comm_ChildInfo_cleanup(ChildInfo *self);
ARM void Knife_Comm_ChildInfo_cleanup(ChildInfo *self) {
    self->flag04 = 1;
    self->id = 0;
    MI_CpuFill8(self->bytes05, 0, 6);
    MI_CpuFill8(self->bytes0e, 0, 0x18);
}
