#include "engine/functions.h"
#include "global.h"
#include "game/multisio.h"

// Send side of the wireless link (0x0204f1c0): packs the packet header bits from the selected table entry.

// MultiSioSendDataSet (0x0204f1c0)
ARM void MultiSioSendDataSet(void *a) {
    MultiSioPacket *packet;
    void *manager;
    void *instance;
    u32 sum;
    u32 i;
    s32 state;

    packet = (MultiSioPacket *)a;
    manager = func_020909c8();
    instance = KnifeApp_getInstance();
    func_0200a3c8(packet->unk_14, data_021350b0[multiSioSelect.index].str08);
    packet->bits.b0 = subtask_getFlag(localPlayerIndex);
    packet->bits.b2 = (data_021350b0[multiSioSelect.index].word00 & 2) != 0;
    packet->bits.b3 = (data_021350b0[multiSioSelect.index].word00 & 1) != 0;
    packet->bits.b4 = (data_021350b0[multiSioSelect.index].word00 & 0x200) != 0;
    packet->bits.b5 = (data_021350b0[multiSioSelect.index].word00 & 0x400) != 0;
    packet->bits.b6 = (data_021350b0[multiSioSelect.index].word00 & 0x1000) != 0;
    packet->bits.b7 = data_021350b0[multiSioSelect.index].b05 >> 2;
    packet->bits.b9 = data_021350b0[multiSioSelect.index].b05;
    packet->bits.b11 = data_021350b0[multiSioSelect.index].b05 >> 4;
    packet->bits.b13 = data_021350b0[multiSioSelect.index].h06;
    packet->bits.b23 = data_021350b0[multiSioSelect.index].b48;
    packet->bits.b30 = 0;
    packet->unk_28 = data_021350b0[multiSioSelect.index].w18;

    if (KnifeApp_isWirelessMode(instance) == 0) {
        ((u8 *)multiSioWork.bufA)[0] = multiSioWork.unk_0b;
        ((u8 *)multiSioWork.bufA)[1] = multiSioWork.unk_02 ^ multiSioWork.unk_03;
        *(u16 *)((u8 *)multiSioWork.bufA + 2) = 0;
        MIi_CpuCopy32(packet, (u8 *)multiSioWork.bufA + 4, 0x14);
        sum = 0;
        for (i = 0; i < 12; i++) {
            sum += ((u16 *)multiSioWork.bufA)[i];
        }
        ((u16 *)multiSioWork.bufA)[1] = (u16)(~sum - 14);
        multiSioWork.sendFlag = 1;
        return;
    }
    state = Knife_Comm_WirelessManager_getState(manager);
    if (state != 8 && state != 0xb) {
        return;
    }
    if (state == 8) {
        packet->unk_30 = multiSioFlags;
    }
    func_0209205c(manager, packet);
}
