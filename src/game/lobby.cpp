#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/lobby.h"

// Functions in this file (original names from the debug build, or provisional names for the others):
//   lobby_setRecvParam (0x020b235c, provisional), getReciveParam (0x020b23b8)

// lobby_setRecvParam(index, flag, value) (0x020b235c, provisional name): ORs the nibble of a player into the receive
// word of the lobby. The nibble is flag << 2 | (value & 3), shifted to the position of the player index
extern "C" void lobby_setRecvParam(s32 index, s32 flag, s32 value);
ARM void lobby_setRecvParam(s32 index, s32 flag, s32 value) {
    U32Table4 shift;
    LobbyState *lobby;

    shift = data_020ded94;
    lobby = *(LobbyState **)(data_02181860 + 4);
    lobby->recvBits |= (flag | (value & 3)) << shift.v[index];
}

// getReciveParam(signed char) (0x020b23b8): the nibble of a player in the received parameter word
extern "C" s32 getReciveParam(s32 index);
ARM s32 getReciveParam(s32 index) {
    U32Table4 shift;

    shift = data_020deda4;
    return (*(u32 *)(*(u8 **)(data_0217d23c + 0x10c) + 0x474) >> shift.v[index]) & 0xf;
}
