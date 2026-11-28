#ifndef SDK_OS_OS_INIT_H
#define SDK_OS_OS_INIT_H

// TwlSDK OS start-up: OSi_InitCommon runs the library initialisers in order.
#include "types.h"

// data_02129b90: set once OSi_InitCommon has filled in the start-up block.
extern u32 data_02129b90;

// Start-up block in the shared area at 0x02fffc30 (0xc bytes), reset to "nothing requested" by OSi_InitCommon.
typedef struct OsStartupBlock {
    u16 unk_00;         // 0x00: 0xffff
    u8 unk_02;          // 0x02: 0xff
    u8 unk_03;          // 0x03: 0xff
    u8 unk_04;          // 0x04: 0xff
    u8 flag0 : 1;       // 0x05: bits 0 and 1 cleared
    u8 flag1 : 1;
    u8 unk_05b2 : 6;
    u16 unk_06;         // 0x06: 0xffff
    u32 unk_08;         // 0x08: 0xffffffff
} OsStartupBlock;

#define OS_STARTUP_BLOCK (*(OsStartupBlock *)0x02fffc30)

#endif
