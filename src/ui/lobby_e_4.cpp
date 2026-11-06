#include "engine/functions.h"
#include "knife/message/lobby_e.h"
#include "ui/widget/uiobject.h"
#include "game/exchange_savedata_api.h"
#include "knife/comm/comm.h"
s8 subtask_getFlag(u32 index);
#include "ui/lobby_color_api.h"
#include "ui/widget/rect_f.h"
#include "ui/groupselectuiview.h"
extern "C" void func_020ac038(s32, s32, void *, void *);

#define LOBBY (*(LobbyState **)(data_02181860 + 4))

extern u8 pauseDialogBuffer[];  // pauseDialogBuffer

// update_confirm() (0x020b3b28): colour confirmation of the lobby. In state 0 the confirm panel slides in; in state 5 the
// parent waits for the slide to end and the children press the button; when everything is confirmed the phase moves on.
// Returns 0
s32 update_confirm(void) {
    s32 zero = 0;
    s32 done = 0;
    u8 *objects;

    switch (LOBBY->unk_39) {
    case 0:
        UIObject_movePos((UIObject *)(LOBBY->objects + 0x108), 0x100000, 0xc0000, data_020de83c, ANIMATION_CURVE_EASE_OUT);
        LOBBY->unk_39 = 5;
        LOBBY->timer = 5;
        objects = LOBBY->objects;
        objects[0x1bc] = 1;
        objects[0x1bd] = done;
        break;
    case 5:
        if (UIObject_getDurationRatio((UIObject *)(LOBBY->objects + 0x58)) == 0x1000) {
            done = 1;
        }
        break;
    case 10:
        break;
    case 15:
        break;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) && is_exchange_savedata_end()) {
        func_0202809c();
    }
    if (done && (((u16 *)playerKeys)[LOBBY->isParent] & 2) && LOBBY->isParent != 0) {
        s8 f = subtask_getFlag(LOBBY->isParent);
        LOBBY->recvBits = (((u32)LOBBY->isParent << 24) >> 16) | 0x2000 | (f & 0xff);
        LOBBY->phase = 3;
        LOBBY->unk_39 = zero;
    }
    if (isFinishedColorChoiceAllPlayers()) {
        LOBBY->timer = LOBBY->timer - 1;
        if (LOBBY->timer == 0) {
            func_0202809c();
            *(s32 *)(*(u8 **)(LOBBY->objects + 0x15c) + 0x14) = zero;
            ResPlayer_SeekAndRefresh(*(void **)(LOBBY->objects + 0x15c), zero);
            func_020ac038(9, (LOBBY->isParent + 1) & 0xff, LOBBY->unk_b8, pauseDialogBuffer);
            LOBBY->phase = 5;
            LOBBY->unk_39 = zero;
            LOBBY->timer = zero;
            SoundReq(0x3e);
            SoundReq(0xc5);
        }
    } else {
        LOBBY->timer = 5;
    }
    if (LOBBY->isParent == 0) {
        if (!isFinishedColorChoiceAllPlayers()) {
            LOBBY->objects[0x10b] = zero;
        }
        addOamUiObj(*(u8 **)(data_0217d23c + 0x10c) + 0x3e0, 0x10, LOBBY->objects + 0x108);
    } else {
        addOamUiObj(*(u8 **)(data_0217d23c + 0x10c) + 0x3e0, 0x10, LOBBY->objects + 0x1b8);
    }
    return 0;
}
