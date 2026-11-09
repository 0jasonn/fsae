#include "engine/functions.h"
#include "knife/comm/wirelessmanager.h"
#include "game/agent_a.h"

// WM_EndDataSharing (0x02020518): stops data sharing on the given work block.
s32 WM_EndDataSharing(void *buf) {
    u8 *base = (u8 *)buf;

    if (base == NULL) {
        return 6;
    }
    if (*(u16 *)(base + 0x80e) == 0) {
        return 3;
    }
    WM_SetPortCallback(*(u16 *)(base + 0x816), 0, 0);
    *(u16 *)(base + 0x80e) = 0;
    *(u16 *)(base + 0x81c) = 0;
    return 0;
}
