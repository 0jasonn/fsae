#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/m4a.h"

// KnifeApp::getInstance (0x0208da4c): creates the application object on first use. It builds the wireless icon, the two
// text tokenizers and the HUD manager, sets the two tables, and registers the KnifeApp destructor.
extern "C" void *KnifeApp_dtor_KnifeApp(void *self);
extern "C" void *KnifeApp_getInstance(void);
ARM void *KnifeApp_getInstance(void) {
    u8 *app;

    if ((data_021763dc & 1) == 0) {
        app = (u8 *)data_021763ec;
        Knife_Comm_WirelessIcon_WirelessIcon(data_021763f0);
        Knife_Message_TextTokenizer_ctor_08e3b4(data_02176430);
        *(void **)(app + 0x80) = data_0211ed90;
        *(void **)(app + 0x108) = data_0211ed30;
        *(void **)(app + 0x144) = data_0211ed30;
        Knife_Message_TextTokenizer_ctor_08e3b4(app + 0x180);
        Knife_Message_TextTokenizer_ctor_08e3b4(app + 0x1bc);
        Knife_Hud_HudManager_ctor(app + 0x1f8);
        *(u32 *)(app + 0x30) = 0;
        Chain_Push(app, (void *)KnifeApp_dtor_KnifeApp, data_021763e0);
        data_021763dc |= 1;
    }
    return data_021763ec;
}
