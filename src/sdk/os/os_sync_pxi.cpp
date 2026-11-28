#include "engine/functions.h"
#include "sdk/os/os_sync_pxi.h"
#include "sdk/pxi/pxi_fifo.h"
#include "sdk/os/os_interrupts.h"

// Notifies the other processor through the PXI FIFO and synchronises the two processors at start-up.
void OSi_SendToPxi(u32 command) {
    while (PXI_SendWordByFifo(0xc, command << 8, 0) != 0) {
    }
}

void OSi_SyncWithOtherProc(u32 role, OsSyncWork *work) {
    u32 count;
    u32 sum;

    if (role == 0) {
        count = 0;
        work->done = 0;
        do {
            work->request = (count & 0xf) | 0x80;
            while (work->request != work->reply && work->done == 0) {
                WaitByLoop(0x400);
            }
            count++;
        } while (work->done == 0);
        work->ready = 1;
    } else {
        sum = 0;
        work->reply = 0;
        do {
            if (work->reply != work->request) {
                work->reply = work->request;
                sum += work->reply;
            } else {
                WaitByLoop(0x400);
            }
        } while ((s32)sum < 0x300);
        work->ready = 0;
        work->done = 1;
        while (work->ready == 0) {
            WaitByLoop(0x400);
        }
    }
}
