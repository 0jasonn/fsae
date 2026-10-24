#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional names): the sound system state at data_02181964 (a byte at +0, the initialized
// flag at +4, the in-init flag at +0xc, and two callback slots at +0x10 and +0x20).
//   SndSys_Init (SndSys_Init), SndSys_Shutdown (SndSys_Shutdown)

extern "C" {
void SND_Init(void);
s32 SND_RecvCommandReply(u32 tag);
void SND_FlushCommand(u32 mode);
void PM_PrependPostExitCallback(void *callback);
void PM_AppendPostExitCallback(void *callback);
void func_020bf3d4(void);
void func_020bfa68(void);
void SndChannel_Reset(void);
void func_020bfb1c(void);
void func_020c02b0(void);
void func_020c02d0(void);
void func_020c1a7c(void);
}
void Menu_ForwardBf40c(s32 a, s32 b, s32 c, s32 d); // C++, src/game/menu_16.cpp

// Sound system state record.
typedef struct SndSysState {
    /* 00 */ s8 status;
    /* 01 */ u8 unk_01[3];
    /* 04 */ s32 initialized;
    /* 08 */ u8 unk_08[4];
    /* 0c */ s32 initializing;
    /* 10 */ void *onExitA;
    /* 14 */ s32 unk_14;
    /* 18 */ u8 unk_18[8];
    /* 20 */ void *onExitB;
    /* 24 */ s32 unk_24;
} SndSysState;
extern SndSysState data_02181964;
extern u8 data_02181974[];
extern u8 data_02181984[];

// SndSys_Init (0x020bf184): sets up the sound system once: SND_Init, the two post exit callbacks, the channel
// bookkeeping (SndChannel_Reset) and the sound helpers.
extern "C" void SndSys_Init(void);
ARM void SndSys_Init(void) {
    if (data_02181964.initializing != 0) {
        return;
    }
    data_02181964.initializing = 1;
    SND_Init();
    data_02181964.onExitA = (void *)func_020bf3d4;
    data_02181964.unk_14 = 0;
    data_02181964.onExitB = (void *)Menu_ForwardBf40c;
    data_02181964.unk_24 = 0;
    PM_PrependPostExitCallback(data_02181974);
    PM_AppendPostExitCallback(data_02181984);
    SndChannel_Reset();
    func_020c02b0();
    func_020bfa68();
    data_02181964.status = -1;
    data_02181964.initialized = 1;
}

// SndSys_Shutdown (0x020bf200): waits until the sound command replies are received, runs the shutdown helpers and
// flushes the command queue.
extern "C" void SndSys_Shutdown(void);
ARM void SndSys_Shutdown(void) {
    while (SND_RecvCommandReply(0) != 0) {
    }
    func_020bfb1c();
    func_020c02d0();
    func_020c1a7c();
    SND_FlushCommand(0);
}
