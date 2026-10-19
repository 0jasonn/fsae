#ifndef WIP_C_NPC_H
#define WIP_C_NPC_H

#include "engine/entity.h"

// NPC script work (0x0c bytes of fields used by the script functions; the rest is not named yet)
struct NPC_WORK_ {
    /* 00 */ u16 unk_00;
    /* 02 */ u8 waitFlag; // non-zero while the NPC is still moving
    /* 03 */ u8 unk_03;
    /* 04 */ u8 scriptArg; // set by script_request / script_move
    /* 05 */ u8 dirArg; // set by script_move
    /* 06 */ u8 unk_06;
    /* 07 */ u8 unk_07;
    /* 08 */ u16 timer;
    /* 0a */ u8 unk_0a[2];
    /* 0c */ Entity *entity; // the object the script controls
    /* 10 */ u16 *script; // current script position, opcode first
};

typedef s32 (*NpcScriptFunc)(NPC_WORK_ *npc);

// Helpers called by the script opcodes (not named yet)
void ScriptJump(NPC_WORK_ *npc, const void *target);

#endif
