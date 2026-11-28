#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/rtc/rtc.h"

// MicWaitBusy() (0x0201a930): spins until the RTC library's busy word leaves 1.
// Written as asm: the ROM keeps the address in ip and the value in r0, which no C form produced (mwcc picks r1 for the
// address); every C variant tried differs in the register of the address only.
asm void MicWaitBusy(void) {
    ldr ip, =data_02129d54
loop:
    ldr r0, [ip]
    cmp r0, #1
    beq loop
    bx lr
}
