#ifndef GAME_COM_H
#define GAME_COM_H

#include "engine/entity.h"

typedef struct ComWork {
    /* 00 */ u8 request;        // request code, set by ComRequest and ComFinish; index into data_020f258c in ComMain
    /* 01 */ u8 phase;          // cleared by ComRequest and ComFinish
    /* 02 */ u8 unk_02;
    /* 03 */ u8 status;         // returned by func_020280e0, cleared by MachiukeStart and MachiukeStop
    /* 04 */ u32 requestFlag;   // 1 after ComRequest, 0 after ComFinish
    /* 08 */ u32 finishArg;     // argument of ComFinish, 0 after ComRequest
    /* 0c */ u16 unk_0c;
    /* 0e */ u8 machiukeActive; // set to 1 by MachiukeStart
} ComWork;

#endif
