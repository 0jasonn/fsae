#include "sdk/card/card.h"

// Checks the boot mode and the media capability bits in the TWL card header.
s32 CARDi_IsNormalMode(void) {
    CardRomHeader *header;

    header = (CardRomHeader *)CARD_GetOwnRomHeaderTWL();
    if (OS_GetBootType() != 1 && header->f5 != 0 && header->f8 == 0) {
        return 1;
    }
    return 0;
}

// Starts a ROM page read with the command selected for normal or TWL mode.
void CARDi_StartRomPageTransfer(u32 page) {
    u32 command;
    volatile u32 *romControl;
    volatile u32 *controlShadow;

    command = 0xb7;
    if (CARDi_IsNormalMode() != 0) {
        command = 0;
    }
    CARDi_SetRomOp(command, page);
    controlShadow = (volatile u32 *)0x02fffae0;
    romControl = (volatile u32 *)0x040001a4;
    *romControl = (*controlShadow & ~0x07000000) | 0xa1000000;
}

// Reads the card ID after selecting the mode-specific command and waiting for the ROM-control ready flag.
u32 CARDi_ReadRomIDCore(void) {
    u32 command;
    u32 control;
    volatile u32 *romControl;
    volatile u32 *controlShadow;

    command = 0xb8;
    if (CARDi_IsNormalMode() != 0) {
        command = 0x90;
    }
    CARDi_SetRomOp(command, 0);
    controlShadow = (volatile u32 *)0x02fffae0;
    romControl = (volatile u32 *)0x040001a4;
    control = *controlShadow & ~0x07000000;
    control |= 0xa7000000;
    control &= ~0x1fff;
    *romControl = control;
    while ((*romControl & 0x00800000) == 0) {
    }
    return *(volatile u32 *)0x04100010;
}
