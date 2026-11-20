#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/lobby.h"

// Latch received lobby bits before clearing both words for the next update.
extern "C" void func_020b2614(void *self, u8 *out);
void func_020b2614(void *self, u8 *out) {
    LobbyState *lobby;
    s8 phaseIndex;
    u32 latched;

    lobby = *(LobbyState **)(data_02181860 + 4);
    phaseIndex = lobby->phase - 1;
    if ((u8)phaseIndex <= 1) {
        (*(LobbyState **)(data_02181860 + 4))->recvBits2 |= 0x800;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        lobby = *(LobbyState **)(data_02181860 + 4);
        latched = lobby->recvBits | ((u32)lobby->recvBits2 << 16);
        *(u32 *)(out + 0x2c) = latched;
    } else {
        u8 **outputSlots = (u8 **)data_0217d348;
        lobby = *(LobbyState **)(data_02181860 + 4);
        *(u32 *)(*outputSlots + 0x474) = lobby->recvBits | ((u32)lobby->recvBits2 << 16);
        lobby = *(LobbyState **)(data_02181860 + 4);
        *(u32 *)(*outputSlots + 0x488) = lobby->recvBits | ((u32)lobby->recvBits2 << 16);
    }
    (*(LobbyState **)(data_02181860 + 4))->recvBits = 0;
    (*(LobbyState **)(data_02181860 + 4))->recvBits2 = 0;
}
