#ifndef WIP_E_LOBBY_E_H
#define WIP_E_LOBBY_E_H

#include "types.h"
// engine/player.h and ui/lobby.h declare data_0212c584 differently; player.h only needs GameState here
#define data_0212c584 shim_data_0212c584
#include "engine/player.h"
#undef data_0212c584
#include "ui/lobby.h"

void MachiukeStop(void);

extern "C" {
void connectCheck(void);
s32 Knife_Comm_WirelessManager_getLinkLevel(void *manager);
BOOL Knife_Message_selectionDialog_isModal(const void *a);
void Knife_Message_selectionDialog_stop(void *a);

s32 update_confirm_wait(void);
void dialog_msg_check(s32 kind, s32 player);
BOOL isFinishedColorConfirmAllPlayers(void);
void subtask_dialogDelete(void);
void SoundReq(u32 a);
void displink(s32 value);
u32 addOamUiObj(void *oamBuffer, u32 size, void *obj);
}

#endif
