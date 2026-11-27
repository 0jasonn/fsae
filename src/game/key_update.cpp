#include "engine/functions.h"
#include "engine/com_work.h"
#include "engine/local_player_index.h"
#include "actor/enemy/comm_check.h"
#include "knife/comm/comm.h"

// key_update(unsigned char), 0x02028894: copies the five key words a remote player sent (newest first) into that
// player's 16-entry key ring in data_02134cb0, stepping the slot back by one (wrapping at 16) for each word. Nothing
// happens for the local player or while the player's packet is not ready.
void key_update(u8 playerNo) {
    ComPacket *packet = &comWork.recv[playerNo];
    u32 slot = comWork.recv[playerNo].keySlot & 0xf;

    if (packet->ready == 0 || playerNo == localPlayerIndex) {
        return;
    }
    (data_02134cb0 + playerNo * 0x10)[slot] = packet->keyHistory[0];
    slot = (slot - 1) & 0xf;
    (data_02134cb0 + playerNo * 0x10)[slot] = packet->keyHistory[1];
    slot = (slot - 1) & 0xf;
    (data_02134cb0 + playerNo * 0x10)[slot] = packet->keyHistory[2];
    slot = (slot - 1) & 0xf;
    (data_02134cb0 + playerNo * 0x10)[slot] = packet->keyHistory[3];
    slot = (slot - 1) & 0xf;
    (data_02134cb0 + playerNo * 0x10)[slot] = packet->keyHistory[4];
}
