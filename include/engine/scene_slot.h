#ifndef ENGINE_SCENE_SLOT_H
#define ENGINE_SCENE_SLOT_H

#include "types.h"

struct OBJ_WORK_;

// NPC/scene slot table (data_02134d30, 8 records of 0x14 bytes up to data_02134dd0). The record type is the original
// NPC_WORK_ (from the mangled names of ScriptMove(NPC_WORK_*) and the script_* opcodes): GetNPC binds a new work to a
// free record (and points the work's linkedEntity back at the record), PutNPC releases it, func_0204f978 clears all
// 0xa0 bytes, and the scenes (opening, ending) drive the fairies and NPCs through the records.
// dsd also has the symbol fairySlots (0x02134d3c = data_02134d30[0].entity) inside this table.
struct NPC_WORK_ {
    /* 00 */ u16 unk_00;    // sequence number (script_seqset); ObjSetTargetWord writes it through linkedEntity
    /* 02 */ u8 waitFlag;   // non-zero while the NPC is still moving (ending scene 00 waits for it to clear)
    /* 03 */ u8 unk_03;
    /* 04 */ u8 scriptArg;  // set by script_request / script_move, and by the ending scenes
    /* 05 */ u8 dirArg;     // set by script_move
    /* 06 */ u8 unk_06;
    /* 07 */ u8 unk_07;
    /* 08 */ u16 timer;
    /* 0a */ u8 unk_0a[2];
    /* 0c */ struct OBJ_WORK_ *entity; // the object the slot (and its script) controls; NULL when the slot is free
    /* 10 */ u16 *script;   // current script position, opcode first
};
extern NPC_WORK_ data_02134d30[8]; // 0x02134d30

#endif
