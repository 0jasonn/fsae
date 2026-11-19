#ifndef ENGINE_COM_WORK_H
#define ENGINE_COM_WORK_H

#include "types.h"

// One communication packet (0x34 bytes): what this machine sends each frame, and what each player sent. The tag is the
// status code the sender is in (0x20/0x21 machiuke, 0x40 random sync, 0x50 key sync, 0x60 wait sync, ...);
// CommStatusSync compares the received tags with the expected status.
typedef struct ComPacket {
    /* 00 */ u8 tag;
    /* 01 */ u8 ready;      // com_machiuke sets 1 once 2 to 4 players are connected and checks it in every recv packet
    /* 02 */ u16 keys;      // pad keys of the sender (playerKeys edge detection reads the received ones)
    /* 04 */ u32 value;     // e.g. the random seed of com_randomsync (data_0212c550)
    /* 08 */ u8 unk_08[0x2c - 0x08];
    /* 2c */ u32 stageFlag; // stagesel relays flag 0x1000 of each player with it (1 = set; stagesel_message sends 1)
    /* 30 */ u32 unk_30;
} ComPacket;

// Communication state block (comWork, 0x148 bytes; ComInitState clears all of it). ComRequest()/ComFinish() set the
// request and its result, ComMain runs the handler of the request (data_020f258c) once per frame, and the handlers
// step through phase. dsd also has the symbols data_0212c9b8 (+0x10, send), data_0212c9ec (+0x44, next) and data_0212ca20
// (+0x78, recv[0], the SubtaskMember view in engine/subtask_status.h) inside this block.
typedef struct ComWork {
    /* 000 */ u8 request;     // request code, set by ComRequest and ComFinish; index into data_020f258c in ComMain
    /* 001 */ u8 phase;       // step of the request handler, cleared by ComRequest and ComFinish
    /* 002 */ u8 counter;     // frame counter/timeout of the current phase
    /* 003 */ u8 status;      // low 4 bits: players taking part (from opTitleState); bit 6: all players ready.
                              // Returned by func_020280e0, cleared by MachiukeStart, MachiukeStop and cockpit_error_check
    /* 004 */ u32 requestFlag; // 1 after ComRequest, 0 after ComFinish
    /* 008 */ u32 result;     // argument of ComFinish (1 done, 5 failed), 2 frame acknowledged (frame_ack), 3 key sync
                              // running, 4 wait sync timed out; 0 after ComRequest. WXC_GetStateCode returns it
    /* 00c */ u16 errorTimer; // frames the players' tags have disagreed (CommErrorCheck gives up after 0x3c)
    /* 00e */ u8 holdFlag;    // nonzero: CommErrorCheck does not check (MachiukeStart, exchange_savedata set it)
    /* 00f */ u8 unk_0f;
    /* 010 */ ComPacket send;    // packet sent this frame (ComUpdate sends and clears it)
    /* 044 */ ComPacket next;    // packet prepared for the next frame (frame_ack copies it into send)
    /* 078 */ ComPacket recv[4]; // packets received from the four players
} ComWork;
extern ComWork comWork; // 0x0212c9a8

#endif
