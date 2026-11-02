#include "engine/functions.h"
#include "knife/message/lobby_e.h"

#define LOBBY (*(LobbyState **)(data_02181860 + 4))
#define LOBBY_MSG (*(u16 *)((u8 *)LOBBY + 0x2c))

// dialog_msg_check(long, long) (0x020b26d0): picks the message id (halfword at +0x2c of the lobby state) shown in the title
// dialog from the lobby phase, and redraws the dialog when it changed. kind is the sort of the dialog, player the player
// index (0 for the local one)
void dialog_msg_check(s32 kind, s32 player) {
    LobbyState *lobby = LOBBY;
    u16 oldMsg = *(u16 *)((u8 *)lobby + 0x2c);
    s32 phase = lobby->phase;
    s32 flag;

    if (phase == 7) {
        return;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
        if (player == 0) {
            if (LOBBY->phase == 0) {
                if (kind == 1) {
                    LOBBY_MSG = 0x83f;
                } else if (kind == 4) {
                    LOBBY_MSG = 0x850;
                } else {
                    LOBBY_MSG = 0x840;
                }
            } else if (LOBBY->phase == 1 || LOBBY->phase == 2 || LOBBY->phase == 4) {
                LOBBY_MSG = 0x84b;
            } else if (LOBBY->phase == 5) {
                if (LOBBY->unk_39 == 1) {
                    LOBBY_MSG = 0x853;
                } else {
                    LOBBY_MSG = 0x852;
                }
            }
        } else {
            phase = LOBBY->phase;
            if (phase == 0) {
                if (kind == 4) {
                    LOBBY_MSG = 0x851;
                } else {
                    LOBBY_MSG = 0x841;
                }
            } else if ((u8)(s8)(phase - 1) <= 1) {
                LOBBY_MSG = 0x84c;
                *((u8 *)LOBBY + 0xa9) = 0;
            } else if (phase == 4) {
                flag = ((s8 *)LOBBY)[(*(u32 *)(*(u8 **)(data_0217d23c + 0x10c) + player * 0x14 + 0x464) << 0x1c) >> 0x1e];
                if (flag != 0) {
                    s32 count = *((s8 *)LOBBY + 0xa9);
                    if (count > 4) {
                        LOBBY_MSG = 0x84b;
                    } else {
                        *((s8 *)LOBBY + 0xa9) = count + 1;
                    }
                } else {
                    LOBBY_MSG = 0x84c;
                }
            } else if (phase == 5) {
                if (LOBBY->unk_39 == 1) {
                    LOBBY_MSG = 0x853;
                } else {
                    LOBBY_MSG = 0x852;
                }
            }
        }
    } else {
        LOBBY_MSG = 0x84d;
    }
    if (oldMsg != LOBBY_MSG) {
        knife_title_dialogDisp(LOBBY_MSG);
    }
}

#define LOBBY (*(LobbyState **)(data_02181860 + 4))
#define LOBBY_MSG (*(u16 *)((u8 *)LOBBY + 0x2c))
