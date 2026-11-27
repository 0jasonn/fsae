#include "engine/functions.h"
#include "knife/comm/multisio.h"
#include "knife/comm/wireless_manager.h"

// MultiSioRecvDataCheck() (0x0204f4a8): collects the packets received this frame into recvData (4 players). Without
// wireless it swaps the receive buffers and keeps every packet whose 12 halfwords sum to -15 (0xfff1); with wireless
// it copies each connected AID's data to its player slot. Returns the bitmask of players whose data arrived.
// One local holds the packet address in the first path and the AID mask in the second, and the packet index is
// reused for the player number: that is how the ROM shares their registers.
u32 MultiSioRecvDataCheck(void *recvData) {
    int (*bufferChange)(void) = set5c_returnZero;
    void *manager = func_020909c8();
    s32 sum;
    volatile u32 check;
    void *tmp;
    u32 j;
    u16 ime;
    u16 result;
    u32 size;
    s32 index;
    s32 aid;
    u32 packetOrMask;
    u8 recvFlag;
    const void *src;

    if (!KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
        check = 0;
        bufferChange();
        ime = REG_IME;
        REG_IME = 0;
        tmp = multiSioWork.bufE;
        multiSioWork.bufE = multiSioWork.bufD;
        multiSioWork.bufD = tmp;
        recvFlag = multiSioWork.unk_05;
        multiSioWork.unk_05 = 0;
        ime = REG_IME;
        REG_IME = 1;
        multiSioWork.unk_03 = 0;
        if (recvFlag != 0) {
            for (index = 0; index < 4; index++) {
                packetOrMask = (u32)((u16 *)multiSioWork.bufE + (u32)(index * 0x1c) / 2);
                sum = 0;
                for (j = 0; j < 0xc; j++) {
                    sum += ((u16 *)packetOrMask)[j];
                }
                if ((s16)sum == -15) {
                    MIi_CpuCopy32((u16 *)packetOrMask + 2, (u8 *)recvData + index * 0x14, 0x14);
                    multiSioWork.unk_03 |= (u8)(1 << index);
                }
                OSi_CpuClear32(0, (u16 *)packetOrMask + 2, 0x14);
            }
        }
        multiSioWork.unk_02 |= multiSioWork.unk_03;
        return multiSioWork.unk_03;
    }
    switch (Knife_Comm_WirelessManager_getState(manager)) {
    case 8:
    case 0xb:
        size = ((Knife::Comm::WirelessManager *)manager)->getSharedDataSize();
        packetOrMask = ((Knife::Comm::WirelessManager *)manager)->getReceivedAIDs();
        result = 0;
        if (Knife_Comm_WirelessManager_getFrameFlag(manager)) {
            return result;
        }
        for (aid = 0; aid < 4; aid++) {
            if (packetOrMask & (1 << aid)) {
                src = ((Knife::Comm::WirelessManager *)manager)->getSharedData(aid);
                if (src != NULL) {
                    index = 0;
                    if (aid != 0) {
                        index = Knife_Comm_GetPlayerNoByAID(aid, (u8 *)recvData + 0x30);
                    }
                    MI_CpuCopy8(src, (u8 *)recvData + index * 0x34, size);
                    result |= (u16)(1 << index);
                }
            }
        }
        return result;
    }
    return 0;
}

// MultiSioVSync() (0x0204f694): per-frame link step in VBlank. With the link started and a packet pending it swaps the
// receive and send buffers, starts a new frame (sync word 0xfefe) and rearms timer 3; before the link has started it
// waits four frames and then sets the timer 3 IRQ check flag in DTCM with interrupts masked.
void MultiSioVSync(void) {
    WirelessManagerWork *manager = (WirelessManagerWork *)func_020909c8();
    void *swap;
    u16 savedIme;

    if (manager->allocator != NULL) {
        return;
    }
    if (multiSioWork.started != 0) {
        if (multiSioWork.sendFlag == 0 || multiSioWork.phase == 0 || multiSioWork.linkFlag == 0) {
            return;
        }
        multiSioWork.unk_18 = -1;
        swap = multiSioWork.bufD;
        multiSioWork.bufD = multiSioWork.bufC;
        multiSioWork.bufC = swap;
        swap = multiSioWork.bufB;
        multiSioWork.bufB = multiSioWork.bufA;
        multiSioWork.bufA = swap;
        multiSioWork.sendFlag = 0;
        multiSioWork.unk_14 = 0;
        multiSioWork.unk_07 = (u32)(multiSioRegs.timerCtrl << 25) >> 31;
        multiSioRegs.timerCount = 0xfefe;
        *(vu16 *)&multiSioRegs.timerCtrl |= 0x80;
        *(vu16 *)0x0400010e = 0xc0;
    } else if (multiSioWork.unk_09 < 4) {
        multiSioWork.unk_09++;
    } else {
        savedIme = REG_IME;
        REG_IME = 0;
        *(volatile u32 *)((u32)data_02fe0000 + 0x3ff8) |= 0x80;
        savedIme = REG_IME;
        REG_IME = 1;
    }
}

// MultiSioIntr() (0x0204f7ac): timer 3 interrupt of the wired link. Copies the four received halfwords, stores them
// into the receive buffer at the current frame position, sends the next halfword of the send buffer and restarts the
// timer while a frame is in progress. A 0xfefe sync word starts a new frame (swaps the buffers and sets the timer 3
// IRQ check flag in DTCM).
// Writing the control word through multiSioRegs.timerCtrl (not the multiSioCtrl alias) gives the ROM's registers.
void MultiSioIntr(void) {
    u16 recv[4];
    s32 i;
    u16 savedIme;

    if (((WirelessManagerWork *)func_020909c8())->allocator != NULL) {
        return;
    }
    *(u64 *)recv = *(u64 *)multiSioRegs.unk_00;
    multiSioWork.unk_07 = (u32)(multiSioRegs.timerCtrl << 25) >> 31;
    if (recv[0] == 0xfefe && (s32)multiSioWork.unk_18 > 0xb) {
        void *swap;
        multiSioWork.unk_18 = -1;
        swap = multiSioWork.bufD;
        multiSioWork.bufD = multiSioWork.bufC;
        multiSioWork.bufC = swap;
        if (multiSioWork.sendFlag != 0) {
            swap = multiSioWork.bufB;
            multiSioWork.bufB = multiSioWork.bufA;
            multiSioWork.bufA = swap;
            multiSioWork.sendFlag = 0;
            multiSioWork.unk_14 = 0;
        }
        savedIme = REG_IME;
        REG_IME = 0;
        *(volatile u32 *)((u32)data_02fe0000 + 0x3ff8) |= 0x80;
        savedIme = REG_IME;
        REG_IME = 1;
    }
    if ((s32)multiSioWork.unk_14 <= 0xb) {
        *(vu16 *)&multiSioRegs.timerCount = ((u16 *)multiSioWork.bufB)[multiSioWork.unk_14];
    }
    if ((s32)multiSioWork.unk_14 < 0xd) {
        multiSioWork.unk_14++;
    }
    if ((s32)multiSioWork.unk_18 >= 0) {
        for (i = 0; i < 4; i++) {
            ((u16 *)multiSioWork.bufC + (u32)(i * 0x1c) / 2)[multiSioWork.unk_18] = recv[i];
        }
        if (multiSioWork.unk_18 == 0xb) {
            multiSioWork.unk_05 = 1;
        }
    }
    if ((s32)multiSioWork.unk_18 < 0xc) {
        multiSioWork.unk_18++;
    }
    if (multiSioWork.started != 0) {
        *(vu16 *)0x0400010e = 0;
    }
    if ((s32)multiSioWork.unk_14 < 0xd && multiSioWork.started != 0) {
        *(vu16 *)&multiSioRegs.timerCtrl |= 0x80;
        *(vu16 *)0x0400010e = 0xc0;
    }
    multiSioWork.unk_09 = 0;
}
