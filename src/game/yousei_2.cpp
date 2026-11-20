#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "engine/blend_request.h"
#include "game/rank_api.h"
#include "actor/object/k_yousei.h"
#include "engine/message_request.h"
#include "game/yousei.h"

extern u8 data_0212c4dc; // demo sub-step
#include "engine/effect_state.h"

// yousei_demo, 0x020820cc. Fairy demo after the stage: the sub-step data_0212c4dc waits for the fairy, checks the
// rupee level and the clear keys of every player, and requests the matching message.
void yousei_demo(void) {
    u8 i;
    switch (data_0212c4dc) {
    case 0:
        if (playerWork[0].entity->action != 2) {
            return;
        }
        data_0212c4dc++;
        effectState.timer = 0x5a;
        em12_typeMasks[0] |= 0x10;
        break;
    case 1: {
        u16 message;
        if ((em12_typeMasks[0] & 0x20) == 0) {
            return;
        }
        effectState.timer = effectState.timer - 1;
        if (effectState.timer != 0) {
            return;
        }
        message = data_02117e10[gameState.unk_01];
        if (func_02081b64() != 0) {
            message += 0x32;
        }
        MessageRequest(message);
        messageRequest.unk_03 = (messageRequest.unk_03 & ~0x1f) | 1;
        messageRequest.unk_04 = (messageRequest.unk_04 & ~0x1f) | 0xe;
        messageRequest.param = gameState.score;
        data_0212c4dc++;
        break;
    }
    case 2:
        if ((messageRequest.phase & 0x7f) != 6) {
            return;
        }
        Status_ArmIfEnabled();
        data_0212c4dc++;
        break;
    case 3:
        if (yousei_msgFinishWait() != 0) {
            return;
        }
        if (getRupeeLevel() == 0) {
            u16 message = 0x131;
            if (func_02081b64() != 0) {
                message += 0x32;
            }
            rupee_error(message);
            return;
        }
        switch (gameState.level) {
        case 0:
        case 1:
            if (ClearKeyCheck() >= 1) {
                for (i = 0; i < gameState.playerCount; i++) {
                    if ((gameState.slots[i].flags & 0x200) == 0) {
                        rupee_error(0x137);
                        return;
                    }
                }
            }
            break;
        case 2:
            if (ClearKeyCheck() >= 2) {
                u8 i;
                for (i = 0; i < gameState.playerCount; i++) {
                    if ((gameState.slots[i].flags & 0x800000) == 0) {
                        rupee_error(0x137);
                        return;
                    }
                }
            }
            if (getRupeeLevel() < 2) {
                rupee_error(0x13c);
                return;
            }
            break;
        case 3:
            if (ClearKeyCheck() == 3) {
                u16 message = 0x13d;
                if (func_02081b64() != 0) {
                    message += 0x32;
                }
                rupee_error(message);
                return;
            }
            if (getRupeeLevel() < 3) {
                rupee_error(0x13c);
                return;
            }
            break;
        }
        effectState.progress = ClearKeyCheck();
        ClearKeyUpdate(gameState.level);
        MessageRequest(RankCheck() + 0x131);
        messageRequest.unk_03 = (messageRequest.unk_03 & ~0x1f) | 1;
        messageRequest.unk_04 = (messageRequest.unk_04 & ~0x1f) | 0xe;
        data_0212c4dc++;
        break;
    case 4:
        if ((messageRequest.phase & 0x7f) != 6) {
            return;
        }
        Status_ArmIfEnabled();
        data_0212c4dc++;
        break;
    case 5:
        if (yousei_msgFinishWait() != 0) {
            return;
        }
        em12_typeMasks[0] |= 0x40;
        if ((em12_typeMasks[0] & 0x80) == 0) {
            return;
        }
        SoundReq(0x216);
        SoundReq(0xf);
        for (i = 0; i < gameState.playerCount; i++) {
            playerWork[i].state = 4;
            playerWork[i].stateTimer = 0x78;
        }
        data_0212c4dc++;
        break;
    case 6:
        if (playerWork[0].entity->action != 2) {
            return;
        }
        em12_typeMasks[0] |= 0x100;
        data_0212c4dc++;
        effectState.timer = 0x3c;
        break;
    case 7: {
        u16 message;
        effectState.timer = effectState.timer - 1;
        if (effectState.timer != 0) {
            return;
        }
        switch (gameState.level) {
        case 1:
            message = ClearKeyCheck() < 1 ? 0x135 : 0x136;
            break;
        case 2:
            message = ClearKeyCheck() < 2 ? 0x138 : 0x139;
            break;
        case 3:
            if (effectState.progress == 3) {
                message = 0x13d;
                if (func_02081b64() != 0) {
                    message += 0x32;
                }
            } else {
                message = ClearKeyCheck() < 3 ? 0x13a : 0x13b;
            }
            break;
        }
        MessageRequest(message);
        messageRequest.unk_03 = (messageRequest.unk_03 & ~0x1f) | 1;
        messageRequest.unk_04 = (messageRequest.unk_04 & ~0x1f) | 0xe;
        goto_nextdemo();
        break;
    }
    }
}

// yousei demo, from 0x02082598: goto_nextdemo sets the demo step to 3 and clears data_0212c4dc.

extern u8 data_0212c500;
extern u8 data_0212c4dc;

// goto_nextdemo (0x02082598)
void goto_nextdemo(void) {
    data_0212c500 = 3;
    data_0212c4dc = 0;
}

// Yousei demo exit and end, 0x020825bc to 0x020826b0.
//   yousei_exit (0x020825bc): three steps. Waits for the fade (messageRequest low bits == 6), then a message, then
//   sets the demo step to 4 and starts the fades and sounds.
//   yousei_end (0x0208265c): clears the backdrop colour, resets the object and text pools and jumps to task 6.

extern u8 data_0212c4dc;     // demo sub-step
extern u8 data_0212c500;     // demo step
#include "engine/palette_buff.h"

// yousei_exit (0x020825bc)
void yousei_exit(void) {
    switch (data_0212c4dc) {
    case 0:
        if ((messageRequest.phase & 0x7f) == 6) {
            Status_ArmIfEnabled();
            data_0212c4dc = data_0212c4dc + 1;
        }
        break;
    case 1:
        if (yousei_msgFinishWait() == 0) {
            data_0212c500 = 4;
            FadeSet(3, 2);
            SoundReq(2 + 0x210);
            if (func_02081b64() != 0) {
                SoundReq(3 + 0x238);
            }
        }
        break;
    }
}

// yousei_end (0x0208265c)
void yousei_end(void) {
    if (blendRequest.blendEnabled != 0) {
        return;
    }
    DispReset();
    *(u16 *)0x5000000 = 0x6739;
    data_021355a0[0] = 0x6739;
    ObjWorkPoolClear();
    ObjMoveInit();
    MessageInitialize();
    TelopInitialize();
    Task_Chain(6);
}
