#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/knife_app.h"
#include "engine/gz_memory.h"
#include "engine/knife_file_2.h"
#include "engine/kmsgreader.h"

// KnifeApp::~KnifeApp (0x0208daec) and KnifeApp::init (0x0208db24).
// The destructor stays a plain extern "C" function: its D0/D1 mangled names cannot be resolved to symbols.txt yet.

// KnifeApp::~KnifeApp (0x0208daec): destroys the sub-objects (at +0x1f8, +0x1bc, +0x180, +0x44 and +0x04)
extern "C" KnifeApp *KnifeApp_dtor_KnifeApp(KnifeApp *self);
ARM KnifeApp *KnifeApp_dtor_KnifeApp(KnifeApp *self) {
    Knife_Hud_HudManager_dtor_HudManager_09e004((u8 *)self + 0x1f8);
    Knife_Message_TextTokenizer_dtor_TextTokenizer_08e3f8((u8 *)self + 0x1bc);
    Knife_Message_TextTokenizer_dtor_TextTokenizer_08e3f8((u8 *)self + 0x180);
    Knife_Message_TextTokenizer_dtor_TextTokenizer_08e3f8((u8 *)self + 0x44);
    Knife_Comm_WirelessIcon_nop((u8 *)self + 0x4);
    return self;
}

// KnifeApp::init (0x0208db24): sets up the GzAllocator over the main arena, makes it the global allocator, enables the
// IRQ bit, initializes the file system and clears the 0x800-byte area at +0x4b0
ARM void KnifeApp::init(void) {
    Gz_Memory_GzAllocator_init((Gz::Memory::GzAllocator *)this, -1);
    func_0208e138(this);
    OS_EnableIrqMask(0x40000);
    Knife::File::System::initialize(0x13);
    MIi_CpuClear16(0, (u8 *)this + 0x4b0, 0x800);
}
