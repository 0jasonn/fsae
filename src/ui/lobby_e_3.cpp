#include "engine/functions.h"
#include "knife/message/lobby_e.h"

#define LOBBY (*(LobbyState **)(data_02181860 + 4))
#define LOBBY_MSG (*(u16 *)((u8 *)LOBBY + 0x2c))

// update_confirm_wait() (0x020b3d70): waits for every player to confirm the colour. When all did, the phase becomes 7
// (timer 30) and the dialog goes away. Until then the A button of the local player confirms (the confirmation is sent
// in the receive bits of a child), and the confirmed state shows the waiting icon. Returns 0
s32 update_confirm_wait(void) {
    s32 confirmed;
    LobbyState *lobby;
    s32 zero;
    s32 isParent;
    u8 *objects;

    if (isFinishedColorConfirmAllPlayers()) {
        (*(LobbyState **)(data_02181860 + 4))->phase = 7;
        (*(LobbyState **)(data_02181860 + 4))->timer = 0x1e;
        zero = 0;
        (*(LobbyState **)(data_02181860 + 4))->unk_39 = zero;
        knife_title_dialogDelete();
        subtask_dialogDelete();
        return zero;
    }
    lobby = *(LobbyState **)(data_02181860 + 4);
    confirmed = lobby->unk_39;
    if (confirmed == 0 && (((u16 *)playerKeys)[lobby->isParent] & 1)) {
        isParent = lobby->isParent;
        if (isParent == 0) {
            *((u8 *)lobby + 4) = 1;
        } else {
            u32 id = isParent & 0xff;
            lobby->recvBits = (id << 8) | 0x3000 | id;
        }
        SoundReq(0x3e);
        (*(LobbyState **)(data_02181860 + 4))->unk_39 = 1;
        objects = (*(LobbyState **)(data_02181860 + 4))->objects;
        objects[0x1bc] = 1;
        objects[0x1bd] = 0;
        return 0;
    }
    if (confirmed != 0) {
        subtask_dialogDelete();
        addOamUiObj(*(u8 **)(data_0217d23c + 0x10c) + 0x3e0, 0x10, (*(LobbyState **)(data_02181860 + 4))->objects + 0x1b8);
    } else {
        displink((*(u32 *)(*(u8 **)(data_0217d23c + 0x10c) + lobby->isParent * 0x14 + 0x464) << 0x1c) >> 0x1e);
    }
    return 0;
}

#define LOBBY (*(LobbyState **)(data_02181860 + 4))
#define LOBBY_MSG (*(u16 *)((u8 *)LOBBY + 0x2c))
