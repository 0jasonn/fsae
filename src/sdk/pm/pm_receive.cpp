#include "engine/functions.h"
#include "engine/wip_a_decls.h"
#include "sdk/pm/pm_callback_api.h"
#include "global.h"
#include "types.h"

extern "C" void func_0218a76c(u32 command);

typedef struct PmCommandCallback {
    void (*callback)(u32 arg);
    u32 arg;
} PmCommandCallback;

// PXI receive callback for power management commands (0x0201c958).
extern "C" void func_0201c958(u32 tag, u32 data, s32 err) {
    u32 commandBits;
    s32 command;
    u16 payload;
    u32 runCallback;

    commandBits = (data & 0x7f00) << 8;
    payload = (u16)(data & 0xff);
    command = (s32)(commandBits >> 16);
    runCallback = 1;

    if (err != 0) {
        PMi_RunCallback((command == 0x61 || command == 0x62) ? 1 : 2);
        return;
    }

    switch (command) {
    case 0x61:
        if (data_0212b920.param3c != 0) {
            *(u16 *)data_0212b920.param3c = payload;
        }
        payload = 0;
        break;
    case 0x60:
        payload = 0;
        break;
    case 0x62:
        break;
    case 0x63:
        *(u32 *)&data_0212b920.unk_00[8] = 1;
        break;
    case 0x70:
        switch (payload) {
        case 0:
            func_0218a76c(1);
            *(u32 *)0x02fff684 = 1;
            break;
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            if (((PmCommandCallback *)0x021bfaf4)->callback != NULL) {
                ((PmCommandCallback *)0x021bfaf4)->callback(((PmCommandCallback *)0x021bfaf4)->arg);
            }
            break;
        case 5:
            func_0218a76c(2);
            *(u32 *)0x02fff684 = 1;
            break;
        }
        runCallback = 0;
        break;
    }

    if (runCallback != 0) {
        PMi_RunCallback(payload);
    }
}
