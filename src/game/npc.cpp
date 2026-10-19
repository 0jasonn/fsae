#include "engine/functions.h"
#include "engine/misc_d.h"
#include "game/npc.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   ObjSetTargetWord -> ObjSetTargetWord, ScriptJump -> ScriptJump, script_nop -> script_nop,
//   script_nop2 -> script_nop2, ScriptMove, script_request, script_seqset, script_message, script_sound, script_move, script_wait_moved,
//   script_wait_timer, script_wait_flag, script_flagset, script_branch, script_chardir, script_message_wait,
//   script_message_close

// Writes the value through the entity pointer in unk_60, when there is one
ARM void ObjSetTargetWord(Entity *e, u16 value) {
    if (e->linkedEntity != 0) {
        *(u16 *)e->linkedEntity = value;
    }
}

// Moves the script position of npc to target
ARM void ScriptJump(NPC_WORK_ *npc, const void *target) {
    npc->script = (u16 *)target;
}

// Script opcode table (one handler per opcode) and the flag words the script conditions read
extern NpcScriptFunc data_021049e4[];
extern const u32 flagBits[];

// Runs script opcodes until one of them asks to wait (returns non-zero)
ARM s32 ScriptMove(NPC_WORK_ *npc) {
    if (npc->script == 0 || npc->script[0] == 0xffff) {
        return 1;
    }
    if (npc->timer != 0) {
        npc->timer--;
        return 0;
    }
    do {
    } while (data_021049e4[npc->script[0]](npc) != 0);
    return 0;
}

// Opcodes that do nothing and only report 0
ARM s32 script_nop(NPC_WORK_ *npc) {
    return 0;
}

// Sets the script argument and steps over the opcode
ARM s32 script_request(NPC_WORK_ *npc) {
    npc->scriptArg = npc->script[1];
    npc->script += 2;
    return 0;
}

// Sets the sequence number and steps over the opcode
ARM s32 script_seqset(NPC_WORK_ *npc) {
    npc->unk_00 = npc->script[1];
    npc->script += 2;
    return 0;
}

// Shows a message (id in the argument) and steps over the opcode
ARM s32 script_message(NPC_WORK_ *npc) {
    MessageRequest(npc->script[1]);
    messageRequest[3] = (messageRequest[3] & ~0x1f) | 1;
    messageRequest[4] = (messageRequest[4] & ~0x1f) | ((u8)npc->script[2] & 0x1f);
    npc->script += 3;
    return 0;
}

// Plays the sound given by the two argument words
ARM s32 script_sound(NPC_WORK_ *npc) {
    SoundReq(((u32)npc->script[1] << 16) | npc->script[2]);
    npc->script += 3;
    return 1;
}

// Starts a move: the NPC gets the mode 3 and the direction argument
ARM s32 script_move(NPC_WORK_ *npc) {
    npc->scriptArg = 3;
    npc->dirArg = npc->script[1];
    npc->entity->direction = npc->script[2];
    npc->unk_06 = npc->entity->direction;
    npc->entity->speed = npc->script[3];
    npc->script += 4;
    return 0;
}

// Waits while the NPC is moving
ARM s32 script_wait_moved(NPC_WORK_ *npc) {
    if (npc->waitFlag == 0) {
        npc->script += 1;
    }
    return 0;
}

// Sets the timer from the argument and steps over the opcode
ARM s32 script_wait_timer(NPC_WORK_ *npc) {
    npc->timer = npc->script[1];
    npc->script += 2;
    return 0;
}

// Waits until the flag in the argument is set
ARM s32 script_wait_flag(NPC_WORK_ *npc) {
    if (data_02134924 & flagBits[npc->script[1]]) {
        npc->script += 2;
    }
    return 0;
}

// Sets the flag in the argument
ARM s32 script_flagset(NPC_WORK_ *npc) {
    data_02134924 |= flagBits[npc->script[1]];
    npc->script += 2;
    return 0;
}

// Calls ScriptJump with the two argument words as one value
ARM s32 script_branch(NPC_WORK_ *npc) {
    ScriptJump(npc, (const void *)(((u32)npc->script[1] << 16) | npc->script[2]));
    return 0;
}

// Turns the entity to the direction given in the argument
ARM s32 script_chardir(NPC_WORK_ *npc) {
    npc->entity->animationState = (u8)npc->script[1];
    npc->script += 2;
    return 0;
}

// Opcode that does nothing and only reports 0
ARM s32 script_nop2(NPC_WORK_ *npc) {
    return 0;
}

// Waits until the message box is idle (state 0 or 6)
ARM s32 script_message_wait(NPC_WORK_ *npc) {
    u8 state;

    state = messageRequest[0] & 0x7f;
    if (state == 0 || state == 6) {
        npc->script += 1;
    }
    return 0;
}

// Closes the message box
ARM s32 script_message_close(NPC_WORK_ *npc) {
    Status_ArmIfEnabled();
    npc->script += 1;
    return 0;
}
