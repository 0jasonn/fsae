#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/ctrl_loadbg.h"

// ctrl_loadbg: function Ctrl_loadBgResources (0x020bbfd0), provisional name Ctrl_loadBgResources.

extern u8 data_02126f9c[];
extern u8 data_02126fc4[];
extern u8 data_02126fe4[];
extern u8 data_02127008[];
extern u8 data_0212702c[];

// Ctrl_loadBgResources() (0x020bbfd0, provisional name): formats a name with the owner flag, looks up the entries it needs
// and loads the three background resources from them.
void Ctrl_loadBgResources(void) {
    char name[0x40];
    u8 block[0x14];
    s32 handle;
    s32 entry14;
    s32 entry10;
    s32 entry0c;
    s32 entry08;

    handle = 0;
    func_0201dc94(name, 0x40, data_02126f9c, OS_getOwnerFlag());
    Ctrl_findEntryD(&handle, name);
    Slots_ClearThreeAt8(block);
    func_020c3dac(handle, 0, 1, block);
    func_020c3dac(handle, 0, 2, block);
    Ctrl_findEntryC(&entry14, data_02126fc4);
    Ctrl_findEntryE(&entry10, data_02126fe4);
    BgLoad_Resources(0, entry10, entry14, handle, 0, 0);
    Ctrl_findEntryE(&entry0c, data_02127008);
    BgLoad_Resources(1, entry0c, 0, 0, 0, 0);
    Ctrl_findEntryE(&entry08, data_0212702c);
    BgLoad_Resources(2, entry08, 0, 0, 0, 0);
}
