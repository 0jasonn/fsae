#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/a_extern.h"

// Restores r4-r11 and sp from a saved context at r0 (fields +0x2c..+0x48 and +0x5c), lowers sp by the word at +0x64
// and jumps to target (r2). Register-only sequence: it never returns to the caller.

// 0x0200ca80
asm void Ctx_RestoreRegsJump(void *context, u32 unused, void (*target)(void)) {
    ldr r4, [r0, #0x2c]
    ldr r5, [r0, #0x30]
    ldr r6, [r0, #0x34]
    ldr r7, [r0, #0x38]
    ldr r8, [r0, #0x3c]
    ldr r9, [r0, #0x40]
    ldr r10, [r0, #0x44]
    ldr r11, [r0, #0x48]
    ldr sp, [r0, #0x5c]
    ldr ip, [r0, #0x64]
    sub sp, sp, ip
    bx r2
}

// Saves r4-r11, sp and lr into a 0x70-byte frame on the stack (zeroing three words at its base), then tail-calls
// RecordCursor_Fetch with the frame address in r0.

// 0x0200cab0
asm void Ctx_SaveFrameThenCall(void) {
    mov ip, sp
    sub sp, sp, #0x70
    str r4, [sp, #0x2c]
    str r5, [sp, #0x30]
    str r6, [sp, #0x34]
    str r7, [sp, #0x38]
    str r8, [sp, #0x3c]
    str r9, [sp, #0x40]
    str r10, [sp, #0x44]
    str r11, [sp, #0x48]
    str ip, [sp, #0x14]
    str ip, [sp, #0x5c]
    str lr, [sp, #0x10]
    mov ip, #0
    str ip, [sp, #0x0]
    str ip, [sp, #0x4]
    str ip, [sp, #0x8]
    mov r0, sp
    b RecordCursor_Fetch
}
