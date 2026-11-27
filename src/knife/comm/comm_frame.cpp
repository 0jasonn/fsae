#include "engine/functions.h"
#include "knife/comm/comm.h"
#include "game/iroyuka.h"
#include "knife/comm/single_play.h"
#include "knife/comm/singleplay_2.h"
#include "knife/comm/singleplay_updatemain.h"
#include "game/ending.h"
#include "engine/com_work.h"
#include "engine/key_ring.h"
#include "engine/message_request.h"
#include "engine/frame_counter.h"
#include "engine/map_state.h"
#include "engine/player.h"
#include "engine/local_player_index.h"
#include "engine/data_0212c500.h"
#include "engine/subtask_status.h"
#include "game/keyread.h"

#include "ui/stagesel_common.h"

// CommFrameUpdate() (0x0202903c): once per frame, puts the local keys (plus 0x1000 while a message is open) into the
// local player's slot of the key ring and copies the last five into comWork.next. In single play it also runs the
// SinglePlay controller (formation/controller change, partner update) and fakes the partner's packet in recv[1].
// Then it advances the ring counter, sends comWork.next and marks the next slot of every other player as empty.
void CommFrameUpdate(void) {
    u16 keys;
    int i;
    ComPacket *packet;
    SinglePlayWork *sp;
    u8 prevCont;

    keys = data_0212c514 | (((u8)(messageRequest.phase & 0x7f)) ? 0x1000 : 0);
    (data_02134cb0 + localPlayerIndex * 0x10)[data_0212c538 & 0xf] = keys;
    comWork.next.keyHistory[0] = (data_02134cb0 + localPlayerIndex * 0x10)[data_0212c538 & 0xf];
    comWork.next.keyHistory[1] = (data_02134cb0 + localPlayerIndex * 0x10)[(data_0212c538 - 1) & 0xf];
    comWork.next.keyHistory[2] = (data_02134cb0 + localPlayerIndex * 0x10)[(data_0212c538 - 2) & 0xf];
    comWork.next.keyHistory[3] = (data_02134cb0 + localPlayerIndex * 0x10)[(data_0212c538 - 3) & 0xf];
    comWork.next.keyHistory[4] = (data_02134cb0 + localPlayerIndex * 0x10)[(data_0212c538 - 4) & 0xf];
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        packet = &comWork.recv[1];
        sp = (SinglePlayWork *)Knife_Single_SinglePlay_GetInstance();
        prevCont = sp->contNo;
        if ((data_0212c4e4 == 2 && data_0212c500 == 9) || (data_0212c4e4 == 10 && data_0212c500 == 4)) {
            if (((u8)(messageRequest.phase & 0x7f)) == 0 && frameCounter.playersBound == 0 && CommKeyCheck(8) == 0
                && frameCounter.pauseRequest == 0) {
                if (playerWork[sp->contNo].callState == 0) {
                    if (playerKeys[0] & 0x400) {
                        if (sp->contChanging == 0) {
                            Knife_Single_SinglePlay_ChangeFormationNo(sp, &playerWork[0], &playerWork[1]);
                        }
                    } else if (playerKeys[0] & 0x300) {
                        if (sp->contChanging != 0) {
                            Knife_Single_SinglePlay_SetFormationNo(sp, 0);
                        } else {
                            Knife_Single_SinglePlay_ChangeContPlayer(sp);
                        }
                    }
                }
                Knife_Single_SinglePlay_Update(sp, &playerWork[0], &playerWork[1], data_0212c514, data_0212c510);
            } else {
                Knife_Single_SinglePlay_UpdatePause(sp, &playerWork[0], &playerWork[1]);
            }
            if (mapState.target == playerWork[0].entity || mapState.target == playerWork[1].entity) {
                mapState.target = playerWork[sp->contNo].entity;
            }
            if (prevCont != sp->contNo) {
                ChangeIroyuka(sp->contNo);
            }
            packet->keyHistory[1] = (data_02134cb0 + 0x10)[(data_0212c538 - 1) & 0xf];
            packet->keyHistory[2] = (data_02134cb0 + 0x10)[(data_0212c538 - 2) & 0xf];
            packet->keyHistory[3] = (data_02134cb0 + 0x10)[(data_0212c538 - 3) & 0xf];
            packet->keyHistory[4] = (data_02134cb0 + 0x10)[(data_0212c538 - 4) & 0xf];
            packet->tag = comWork.next.tag;
            packet->keySlot = data_0212c538;
            packet->ready = 1;
            if (sp->contNo != 0) {
                packet->keys = (data_0212c514 & ~8) | (((u8)(messageRequest.phase & 0x7f)) ? 0x1000 : 0);
                packet->keys &= ~sp->keysOff;
                if (frameCounter.pauseRequest != 0) {
                    (data_02134cb0 + localPlayerIndex * 0x10)[data_0212c538 & 0xf] |= 0x1000;
                    comWork.next.keyHistory[0] = (data_02134cb0 + localPlayerIndex * 0x10)[data_0212c538 & 0xf];
                } else {
                    // keys and i are reused as temporaries here and below (needed for the original register use)
                    keys = sp->keysOn;
                    i = (((u8)(messageRequest.phase & 0x7f)) ? 0x1000 : 0);
                    (data_02134cb0 + localPlayerIndex * 0x10)[data_0212c538 & 0xf] = (data_0212c514 & 0x708) | (i | keys);
                    comWork.next.keyHistory[0] = (data_02134cb0 + localPlayerIndex * 0x10)[data_0212c538 & 0xf];
                }
            } else {
                comWork.next.keyHistory[0] &= ~sp->keysOff;
                (data_02134cb0 + localPlayerIndex * 0x10)[data_0212c538 & 0xf] = comWork.next.keyHistory[0];
                i = (((u8)(messageRequest.phase & 0x7f)) ? 0x1000 : 0);
                packet->keys = i | sp->keysOn;
            }
        } else {
            packet->keyHistory[1] = (data_02134cb0 + 0x10)[(data_0212c538 - 1) & 0xf];
            packet->keyHistory[2] = (data_02134cb0 + 0x10)[(data_0212c538 - 2) & 0xf];
            packet->keyHistory[3] = (data_02134cb0 + 0x10)[(data_0212c538 - 3) & 0xf];
            packet->keyHistory[4] = (data_02134cb0 + 0x10)[(data_0212c538 - 4) & 0xf];
            packet->tag = comWork.next.tag;
            packet->ready = 1;
            packet->keySlot = data_0212c538;
            packet->keys = 0;
        }
        packet->bits.b0 = subtask_getFlag(1);
    }
    comWork.next.keySlot = data_0212c538;
    data_0212c538++;
    comWork.next.ready = 1;
    MIi_CpuCopy32(&comWork.next, &comWork.send, 0x34);
    for (i = 0; i < 4; i++) {
        if (i != localPlayerIndex) {
            (data_02134cb0 + i * 0x10)[(data_0212c538 - 1) & 0xf] = 0xc000;
        }
    }
}
