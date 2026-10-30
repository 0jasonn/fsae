#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Task state record at data_02127280 (bss).
typedef struct TaskState {
    void (*pending)(void);    // 0x00: run and cleared by Task_Dispatch
    void (*callback)(void);    // 0x04: run once by Task_Flush while the task is not active
    u32 queued;           // 0x08: entries waiting in the table at Task_QueueTable
    u32 active;           // 0x0c
} TaskState;

extern TaskState data_02127280;

extern "C" void func_0200813c(s32 value);
extern "C" void Chain_Drain(void);
extern "C" void Task_Dispatch(s32 flag);
extern "C" void Task_Flush(s32 flag);
extern "C" void Task_Start(void);

// Marks the task active and flushes it with flag 1.
ARM void Task_Start(void) {
    func_0200813c(1);
    data_02127280.active = 1;
    Task_Flush(1);
}

// When the task is not active, runs the pending callback once; then dispatches the queue with flag.
ARM void Task_Flush(s32 flag) {
    if (data_02127280.active == 0) {
        Chain_Drain();
        if (data_02127280.callback != NULL) {
            data_02127280.callback();
            data_02127280.callback = NULL;
        }
    }
    Task_Dispatch(flag);
}
