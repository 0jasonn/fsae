#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/singleplay.h"

// Knife::Single::SinglePlay::Initialize() (0x02093bbc): the SinglePlay object is the controller state (SinglePlayWork in
// single_play_d.h). The original is a member with `this` in r0 and the mangled name _Z34Knife_Single_SinglePlay_Initializev
// (flattened in symbols.txt), so the body is written as assembly: it clears the controller fields, sets the key mask at
// +0x20 to 0xffff and tail-calls the log list initializer (SinglePlayLogList::Initialize) on the list at +0x34.

asm void Knife_Single_SinglePlay_Initialize(void) {
    ldr r1, =0xffff
    mov r2, #0x0
    ldr ip, =_ZN5Knife6Single10SinglePlay17SinglePlayLogList10InitializeEv
    strb r2, [r0, #0x0]
    strb r2, [r0, #0x1]
    strh r2, [r0, #0x14]
    strb r2, [r0, #0x2]
    strb r2, [r0, #0x3]
    strb r2, [r0, #0x4]
    strb r2, [r0, #0x5]
    strb r2, [r0, #0x6]
    strb r2, [r0, #0x8]
    strb r2, [r0, #0x9]
    strb r2, [r0, #0xa]
    strh r2, [r0, #0x2a]
    strh r2, [r0, #0x28]
    strh r2, [r0, #0x26]
    strh r2, [r0, #0x24]
    strb r2, [r0, #0xb]
    strb r2, [r0, #0xc]
    strh r2, [r0, #0x1e]
    strh r2, [r0, #0x1c]
    strh r1, [r0, #0x20]
    strb r2, [r0, #0xe]
    strb r2, [r0, #0x11]
    strb r2, [r0, #0x10]
    strh r2, [r0, #0x2e]
    strh r2, [r0, #0x2c]
    str r2, [r0, #0x30]
    strb r2, [r0, #0x12]
    strh r2, [r0, #0x1a]
    add r0, r0, #0x34
    bx ip
}
