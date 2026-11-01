#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wirelessmanager.h"

// Knife::Comm::WirelessManager::stepNextChannel() (0x02092590). Finds the lowest allowed channel at or above the current
// channel index (channel) in the channel mask (channelMask, 16 bits): channel becomes its bit number plus one, or 0 when no
// allowed channel is left. The lowest set bit is found with clz (x & ~x-1 gives the bits below it), which has no C form
// here, so the whole body is written in ARM assembly.

// Register use: r0 = manager, r2 = manager + 0x1000 (the channel index at +0x1cbc), r1 = channel mask (+0x1cce).
asm void Knife_Comm_WirelessManager_stepNextChannel(void *self) {
    add r2, r0, #0x1000
    ldr r1, [r2, #0xcbc]
    mov r3, #0x1
    mov r3, r3, lsl r1
    add r1, r0, #0x1c00
    sub r3, r3, #0x1
    ldrh ip, [r1, #0xce]
    mvn r3, r3
    mov r1, r3, lsl #0x10
    ands r1, ip, r1, lsr #0x10
    moveq r0, #0x0
    streq r0, [r2, #0xcbc]
    bxeq lr
    mvn r2, r1
    sub r1, r1, #0x1
    and r1, r2, r1
    clz r1, r1
    rsb r1, r1, #0x20
    add r1, r1, #0x1
    add r0, r0, #0x1000
    str r1, [r0, #0xcbc]
    bx lr
}
