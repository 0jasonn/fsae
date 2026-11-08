#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "game/rank_api.h"
#include "actor/object/k_yousei.h"

extern u8 data_0212c4dc; // demo sub-step
extern u8 effectState[]; // u16 timer at +4, byte +8: clear level

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
        *(u16 *)(effectState + 4) = 0x5a;
        em12_typeMasks[0] |= 0x10;
        break;
    case 1: {
        u16 message;
        if ((em12_typeMasks[0] & 0x20) == 0) {
            return;
        }
        *(u16 *)(effectState + 4) = *(u16 *)(effectState + 4) - 1;
        if (*(u16 *)(effectState + 4) != 0) {
            return;
        }
        message = data_02117e10[gameState.unk_01];
        if (func_02081b64() != 0) {
            message += 0x32;
        }
        MessageRequest(message);
        messageRequest[3] = (messageRequest[3] & ~0x1f) | 1;
        messageRequest[4] = (messageRequest[4] & ~0x1f) | 0xe;
        *(u32 *)(messageRequest + 8) = gameState.score;
        data_0212c4dc++;
        break;
    }
    case 2:
        if ((messageRequest[0] & 0x7f) != 6) {
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
        effectState[8] = ClearKeyCheck();
        ClearKeyUpdate(gameState.level);
        MessageRequest(RankCheck() + 0x131);
        messageRequest[3] = (messageRequest[3] & ~0x1f) | 1;
        messageRequest[4] = (messageRequest[4] & ~0x1f) | 0xe;
        data_0212c4dc++;
        break;
    case 4:
        if ((messageRequest[0] & 0x7f) != 6) {
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
        *(u16 *)(effectState + 4) = 0x3c;
        break;
    case 7: {
        u16 message;
        *(u16 *)(effectState + 4) = *(u16 *)(effectState + 4) - 1;
        if (*(u16 *)(effectState + 4) != 0) {
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
            if (effectState[8] == 3) {
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
        messageRequest[3] = (messageRequest[3] & ~0x1f) | 1;
        messageRequest[4] = (messageRequest[4] & ~0x1f) | 0xe;
        goto_nextdemo();
        break;
    }
    }
}
