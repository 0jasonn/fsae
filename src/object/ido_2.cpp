#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/g_callees.h"

// Ido player check, second unit (module ido). Address -> name:
//   0x020650a0 ido_yukaPlMoveCheck (original name yukaPlMoveCheck(PL_WORK_*))

extern "C" int ido_yukaPlMoveCheck(PlayerData *player);

ARM int ido_yukaPlMoveCheck(PlayerData *player) {
    if ((((u32)((u8 *)player)[0x8b]) << 25) >> 29) {
        return 1;
    }
    if (player->unk_08 == 0x1ac) {
        return 1;
    }
    if (player->unk_02 != 0 && player->unk_02 != 0x25) {
        return 0;
    }
    return func_020860dc(player->entity) != 0;
}
