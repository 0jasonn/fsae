#include "engine/functions.h"
#include "knife/message/lobby.h"
#include "global.h"
#include "types.h"
#include "ui/lobby.h"
#include "ui/lobby_api.h"

#define LOBBY (*(LobbyState **)(data_02181860 + 4))
#define LOBBY_MSG (*(u16 *)((u8 *)LOBBY + 0x2c))

// connectCheck() (0x020b2190): watches the wireless link during the lobby. A parent that lost its children (or that has fewer
// than the game needs) ends the group; when the state of the link does not fit the phase (parent not in state 8, child not
// in state 11) the lobby is left: phase 8, the dialog is removed and the error flags (data_0217d23c +0xd0 to +0xd2) are set
void connectCheck(void) {
    BOOL one = TRUE;
    void *manager = func_020909c8();
    s32 state;
    BOOL parentLost;
    BOOL childLost;
    LobbyState *lobby;

    state = Knife_Comm_WirelessManager_getState(manager);
    parentLost = FALSE;
    childLost = FALSE;
    lobby = LOBBY;
    if ((u8)(s8)(lobby->phase - 4) <= 2 && lobby->unk_a4 != 0) {
        if ((s8)lobby->playerCount == 1 || gameState.playerCount > Knife_Comm_WirelessManager_getLinkLevel(manager)) {
            parentLost = TRUE;
            Knife_Comm_WirelessManager_endParent(manager);
        }
    }
    if (LOBBY->phase != 8) {
        if (LOBBY->unk_a4 != 0) {
            if (state != 8) {
                parentLost = TRUE;
            }
        } else if (state != 0xb) {
            childLost = TRUE;
        }
    }
    if (parentLost) {
        MachiukeStop();
        LOBBY->timer = 2;
        LOBBY->phase = 8;
        data_0217d23c[0xd0] = one;
        data_0217d23c[0xd1] = 3;
        *(s8 *)(data_0217d23c + 0xd2) = -1;
        subtask_dialogDelete();
        if (Knife_Message_selectionDialog_isModal(pauseDialogWindow)) {
            Knife_Message_selectionDialog_stop(pauseDialogWindow);
            subTaskSendScr(0, pauseDialogBuffer, 0, 0x400);
        }
        SoundReq(0x40);
    }
    if (childLost) {
        MachiukeStop();
        LOBBY->timer = 2;
        LOBBY->phase = 8;
        *((u8 *)LOBBY + 0xa8) = one;
        data_0217d23c[0xd0] = 2;
        data_0217d23c[0xd1] = 3;
        *(s8 *)(data_0217d23c + 0xd2) = -1;
        subtask_dialogDelete();
        if (Knife_Message_selectionDialog_isModal(pauseDialogWindow)) {
            Knife_Message_selectionDialog_stop(pauseDialogWindow);
            subTaskSendScr(0, pauseDialogBuffer, 0, 0x400);
        }
        SoundReq(0x40);
    }
}

#define LOBBY (*(LobbyState **)(data_02181860 + 4))
#define LOBBY_MSG (*(u16 *)((u8 *)LOBBY + 0x2c))

// Functions in this file (original names from the debug build, or provisional names for the others):
//   lobby_setRecvParam (0x020b235c, provisional), getReciveParam (0x020b23b8)

// lobby_setRecvParam(index, flag, value) (0x020b235c, provisional name): ORs the nibble of a player into the receive
// word of the lobby. The nibble is flag << 2 | (value & 3), shifted to the position of the player index
void lobby_setRecvParam(s32 index, s32 flag, s32 value) {
    U32Table4 shift;
    LobbyState *lobby;

    shift = data_020ded94;
    lobby = *(LobbyState **)(data_02181860 + 4);
    lobby->recvBits |= (flag | (value & 3)) << shift.v[index];
}

// getReciveParam(signed char) (0x020b23b8): the nibble of a player in the received parameter word
s32 getReciveParam(s32 index) {
    U32Table4 shift;

    shift = data_020deda4;
    return (*(u32 *)(*(u8 **)(data_0217d23c + 0x10c) + 0x474) >> shift.v[index]) & 0xf;
}
