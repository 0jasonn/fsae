#include "engine/functions.h"
#include "knife/comm/comm.h"
#include "knife/message/lobby.h"
#include "knife/comm/wirelessmanager.h"
#include "engine/player.h"
#include "engine/effect_state.h"
#include "engine/blend_request.h"
#include "engine/com_work.h"
#include "engine/multisio_save.h"
#include "engine/string16_copy.h"
#include "game/keyread.h"

// Connection data sent to the parent with Knife::Comm::WirelessManager::connect (0x34 bytes are sent; the name, the
// packed status bits and the rupee value are the start of the member record that ends up in comWork.recv[]).
typedef struct TitleConnectInfo {
    /* 00 */ u16 name[8];
    /* 10 */ ComPacketBits bits;
    /* 14 */ u32 value;
} TitleConnectInfo;

// The save index is read through a cast pointer: mwcc then reloads it after every store into the (address-taken)
// connect data, as the original does; a plain multiSioSelect.index is loaded once.
#define SELECTED_ENTRY (data_021350b0[((MultiSioSelect *)&multiSioSelect)->index])

// title_machiuke() (0x02052b3c): the title screen waiting for the other players. B leaves the screen (after a short
// guard time following a held A or B). Offline, once the link has been up for two seconds A or START starts the game.
// Online, the wireless manager is shut down on leaving, reset when it reports an error, connects to the first parent
// found while scanning (state 5) and once connected (states 8 and 11) A or START starts the game.
void title_machiuke(void) {
    TitleConnectInfo info;
    void *manager;
    void *app;
    s32 state;
    s32 parentCount;
    s32 i;
    void *parent;

    parentCount = 0; // also the 0 every exit path below stores (the original reuses it)
    manager = func_020909c8();
    app = KnifeApp_getInstance();
    if (effectState.timer != 0) {
        effectState.timer--;
    }
    if (data_0212c514 & 9) {
        effectState.timer = 4;
    }
    if (!KnifeApp_isWirelessMode(app)) {
        if (effectState.timer == 0 && (data_0212c510 & 2)) {
            data_0212c4dc--;
            MachiukeStop();
            MakeFadeBuff256(parentCount);
            title_MakeFadeBuff256(blendRequest.blendColor, parentCount);
            blendRequest.resetValue = parentCount - 1;
            PaletteFade_ClearBufferFlag();
            effectState.messageIndex = parentCount;
            return;
        }
        if (func_020280e0() & 0x40) {
            if (++effectState.frames <= 0x78) {
                return;
            }
            effectState.progress |= 0x80;
            title_machiuke_joy();
            if (playerKeys[0] & 9) {
                effectState.phase = parentCount;
                data_0212c4dc++;
                gameState.playerCount = CountBits(func_020280e0() & 0xf);
                func_0202809c();
                blendRequest.resetValue = parentCount - 1;
                PaletteFade_ClearBufferFlag();
                FadeSet(3, 8);
                SoundReq(0x80040000);
            }
            playerKeys[0] = parentCount;
        } else {
            effectState.progress &= 0x7f;
            effectState.frames = parentCount;
        }
        return;
    }
    state = Knife_Comm_WirelessManager_getState(manager);
    if (func_02090ecc(manager)) {
        return;
    }
    if (state == 2) {
        Knife_Comm_WirelessManager_turnOff(manager);
        while (state != 0) {
            OS_WaitVBlankIntr();
            Knife_Comm_WirelessManager_update(manager);
            state = Knife_Comm_WirelessManager_getState(manager);
        }
        data_0212c4dc--;
        MachiukeStop();
        MakeFadeBuff256(parentCount);
        title_MakeFadeBuff256(blendRequest.blendColor, parentCount);
        blendRequest.resetValue = parentCount - 1;
        PaletteFade_ClearBufferFlag();
        effectState.messageIndex = parentCount;
    } else if (state == 0xe || state == 0xf) {
        Knife_Comm_WirelessManager_reset(manager);
    } else if (state == 5) {
        parentCount = Knife_Comm_WirelessManager_getMaxParents(manager);
        for (i = 0; i < parentCount; i++) {
            parent = Knife_Comm_WirelessManager_getScanResult(manager, i);
            if (parent != NULL) {
                Knife_Comm_WirelessManager_reset(manager);
                while (state != 2) {
                    OS_WaitVBlankIntr();
                    Knife_Comm_WirelessManager_update(manager);
                    state = Knife_Comm_WirelessManager_getState(manager);
                }
                func_0200a3c8(info.name, SELECTED_ENTRY.str08);
                info.bits.b0 = 0;
                info.bits.b2 = (SELECTED_ENTRY.word00 & 2) != 0;
                info.bits.b3 = (SELECTED_ENTRY.word00 & 1) != 0;
                info.bits.b4 = (SELECTED_ENTRY.word00 & 0x200) != 0;
                info.bits.b5 = (SELECTED_ENTRY.word00 & 0x400) != 0;
                info.bits.b6 = (SELECTED_ENTRY.word00 & 0x1000) != 0;
                info.bits.b7 = SELECTED_ENTRY.b05 >> 2;
                info.bits.b9 = SELECTED_ENTRY.b05;
                info.bits.b11 = SELECTED_ENTRY.b05 >> 4;
                info.bits.b13 = SELECTED_ENTRY.h06;
                info.value = SELECTED_ENTRY.w18;
                info.bits.b30 = 0;
                info.bits.b23 = SELECTED_ENTRY.b48;
                if (!Knife_Comm_WirelessManager_connect(manager, parent, 0x34, &info)) {
                    SoundReq(0x40);
                } else {
                    SoundReq(0x3e);
                }
                return;
            }
        }
        if (effectState.timer == 0 && (data_0212c510 & 2)) {
            Knife_Comm_WirelessManager_reset(manager);
        }
    } else if (state == 8 || state == 0xb) {
        if (effectState.timer == 0 && (data_0212c510 & 2)) {
            Knife_Comm_WirelessManager_reset(manager);
            return;
        }
        if (func_020280e0() & 0x40) {
            if (++effectState.frames <= 0x78) {
                return;
            }
            effectState.progress |= 0x80;
            title_machiuke_joy();
            if (playerKeys[0] & 9) {
                effectState.phase = 0;
                data_0212c4dc++;
                if (state == 8) {
                    Knife_Comm_WirelessManager_setEntry(manager, FALSE);
                }
                gameState.playerCount = CountBits(func_020280e0() & 0xf);
                func_0202809c();
                blendRequest.resetValue = -1;
                PaletteFade_ClearBufferFlag();
                FadeSet(3, 8);
                SoundReq(0x80040000);
            }
            playerKeys[0] = parentCount;
        } else {
            effectState.progress &= 0x7f;
            effectState.frames = parentCount;
        }
    }
}
