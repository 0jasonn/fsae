#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Frame fragments of the scope-cleanup run at 0x0200c7a4..0x0200c8c4 (the 0x0200c75c loop is parked). Each function
// uses the frame pointer r11 and the cleanup object at the frame, which C cannot express, so the bodies are instructions.
void CallHook_0200c55c(void);
extern "C" void func_0200c75c(u32 start, u32 end, u32 step, void (*fn)(u32));
void Ctx_SaveFrameThenCall(void);
extern "C" void Cleanup_Invoke(void *self);
extern "C" void Frame_LoopC868(u32 base, u32 count, u32 step, void (*callback)(u32));

// 0x0200c7a4: frame tail. Calls CallHook_0200c55c, runs Cleanup_Invoke on the frame object at r11 and pops the 0x18-byte frame.
asm void Frame_TailC7a4(void) {
    bl CallHook_0200c55c
    add r0, r11, #0x0
    bl Cleanup_Invoke
    add sp, r11, #0x18
    ldmia sp!, {r4, r5, r6, r7, r11, pc}
}

// 0x0200c7b8: loop of callbacks over a frame. When the flag at frame+0x38 is set and the count is nonzero, the callback
// is called for each step with the cursor kept in r8 and the frame pointer stored at frame+0x14. The flag clear path
// steps the callback pointer with r7. The block after the first return path is the frame tail that the ROM keeps
// (func_0200c75c, Ctx_SaveFrameThenCall and Cleanup_Invoke). Written as instructions: the frame pointer r11 has no C form.
asm void Frame_LoopC7b8(void *array, s32 count, u32 size, void *ctor, void *dtor) {
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r11, lr}
    sub sp, sp, #0x18
    mov r11, sp
    movs r4, r3
    mov r7, r0
    mov r6, r1
    mov r5, r2
    addeq sp, r11, #0x18
    ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r11, pc}
    ldr r0, [r11, #0x38]
    cmp r0, #0x0
    beq c7b8_flag_clear
    mov r8, r7
    str sp, [r11, #0x14]
    cmp r6, #0x0
    addeq sp, r11, #0x18
    ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r11, pc}
c7b8_step_loop:
    mov r0, r8
    blx r4
    add r8, r8, r5
    subs r6, r6, #0x1
    bne c7b8_step_loop
    add sp, r11, #0x18
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r11, pc}
    ldr r3, [r11, #0x38]
    mov r0, r7
    mov r1, r8
    mov r2, r5
    bl func_0200c75c
    bl Ctx_SaveFrameThenCall
    add r0, r11, #0x0
    bl Cleanup_Invoke
    add sp, r11, #0x18
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r11, pc}
c7b8_flag_clear:
    cmp r6, #0x0
    addeq sp, r11, #0x18
    ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r11, pc}
c7b8_clear_loop:
    mov r0, r7
    blx r4
    add r7, r7, r5
    subs r6, r6, #0x1
    bne c7b8_clear_loop
    add sp, r11, #0x18
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r11, pc}
}

// 0x0200c868: calls callback(p) for p = base + count * step - step * k, k = 1..count (descending), when callback is set
// and count is nonzero. It runs in a frame with r11 = sp and stores sp at frame+0x14 when step is nonzero, which C
// cannot express (the frame pointer is the local's address); written as instructions.
asm void Frame_LoopC868(u32 base, u32 count, u32 step, void (*callback)(u32)) {
    stmdb sp!, {r4, r5, r6, r7, r11, lr}
    sub sp, sp, #0x18
    mov r11, sp
    mov r7, r1
    movs r5, r3
    mov r6, r2
    mlane r4, r7, r6, r0
    strne sp, [r11, #0x14]
    cmpne r7, #0x0
    addeq sp, r11, #0x18
    ldmeqia sp!, {r4, r5, r6, r7, r11, pc}
loop_c868:
    sub r4, r4, r6
    mov r0, r4
    blx r5
    subs r7, r7, #0x1
    bne loop_c868
    add sp, r11, #0x18
    ldmia sp!, {r4, r5, r6, r7, r11, pc}
}

// 0x0200c8b0: the same frame tail as 0x0200c7a4.
asm void Frame_TailC8b0(void) {
    bl CallHook_0200c55c
    add r0, r11, #0x0
    bl Cleanup_Invoke
    add sp, r11, #0x18
    ldmia sp!, {r4, r5, r6, r7, r11, pc}
}
