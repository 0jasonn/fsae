#ifndef WIP_A_COMERROR_H
#define WIP_A_COMERROR_H

#include "engine/functions.h"

// Data used by the communication error screen (not in engine/functions.h or engine/misc.h yet)
extern u8 data_0212c4c8;
extern u8 data_0212c4c4;
extern u8 data_0212c4d8;
extern u8 data_0212c4dc;
extern u16 data_0212c510;
extern u8 data_020f25a8[];
extern u8 data_020f25b4[];
extern u8 effectState[];   // ResultState block (enemy/ending.h): u16 timer at +4
extern u16 data_021355a0;
extern void (*data_0212c564)(void);
extern const u8 data_020ce4d0[];

// Declared where functions.h has no prototype yet (plain symbols, extern "C")
extern "C" {
void OS_WaitVBlankIntr(void);
void Knife_Comm_WirelessManager_update(void *manager);
void comerror_init(void);  // 0x02028c44
void comerror_move(void);  // 0x02028e70
}

#endif
