#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/subtask.h"
#include "game/lobby.h"

// Functions in this file (original names from the debug build):
//   subTask_lobby_end (0x020b1920)

// subTask_lobby_end() (0x020b1920): ends the lobby subtask. Deletes the title dialog, frees the four lobby blocks and
// the object info blocks, stops the room and the fade, and clears the wireless flag of the exchange state when the
// device is in wireless mode
extern "C" void subTask_lobby_end(void);
ARM void subTask_lobby_end(void) {
    u32 slot;

    knife_title_dialogDelete();
    func_0208e188((*(LobbyState **)(data_02181860 + 4))->objects);
    func_0208e188((*(LobbyState **)(data_02181860 + 4))->unk_b0);
    func_0208e188((*(LobbyState **)(data_02181860 + 4))->unk_b4);
    func_0208e188((*(LobbyState **)(data_02181860 + 4))->unk_b8);
    for (slot = 0; slot < 4; slot++) {
        subTask_free_slot(slot);
    }
    subTask_free_objinfo((OBJInfo *)data_0217a258);
    subTask_free_objinfo((OBJInfo *)(*(u8 **)(data_02181860 + 4) + 0x3c));
    func_0209bee4();
    Knife_Message_CleanupTextRenderer();
    if ((*(LobbyState **)(data_02181860 + 4))->phase != 8 && (*(LobbyState **)(data_02181860 + 4))->phase != 7) {
        eff_fade_out_init(0x1000);
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        data_0212c9a8[0x0e] = 0;
    }
}
