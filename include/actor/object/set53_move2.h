#ifndef ACTOR_OBJECT_SET53_MOVE2_H
#define ACTOR_OBJECT_SET53_MOVE2_H

#include "engine/functions.h"
#include "engine/player.h"
#include "actor/object/set53_row.h"

// SinglePlay object as constructed on the stack (Knife::Single::SinglePlay, 0xc44 bytes): the state block followed by
// the log list. The inline constructor runs SinglePlayLogList::SinglePlayLogList on the list and then
// SinglePlay::Initialize; the inline destructor runs Initialize again.
typedef struct SinglePlayObject {
    u8 contNo;          // 0x00: the controlling player
    u8 contChanging;    // 0x01
    u8 unk_02[0x32];
    u8 logList[0xc10];  // 0x34: SinglePlayLogList
} SinglePlayObject;

extern "C" {
void Knife_Single_SinglePlay_SinglePlayLogList_SinglePlayLogList(void *self);
// Knife::Single::SinglePlay::Initialize() (0x02093bbc) with its `this`, under the symbol name symbols.txt gives it
void _Z34Knife_Single_SinglePlay_Initializev(void *self);
// Knife::Single::SinglePlay::SinglePlayLogList::Initialize() (0x0209a060) with its `this`
void _ZN5Knife6Single10SinglePlay17SinglePlayLogList10InitializeEv(void *self);
}

#endif
