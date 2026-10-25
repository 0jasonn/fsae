#include "engine/functions.h"
#include "global.h"

// Staffroll step machine (module sr): StaffrollTask runs the step at data_0212c500 of srStepTable, sr_wait waits for the
// communication to report that the step is complete. data_0212c4dc is the phase inside the wait.
//   StaffrollTask (0x02077810), sr_wait (0x0207790c).

extern u8 data_0212c4dc;             // phase of sr_wait: 0 requests, 1 waits for the state code, then the step advances
extern u8 data_0212c500;             // step index into srStepTable
extern void (*srStepTable[])(void); // srStepTable: sr_init, sr_wait, sr_makemap, sr_start, sr_main, ...
extern u32 data_0212c550;
extern u32 data_0212c554;
extern u16 data_0212c75c;            // display shadow flags (first halfword)

extern "C" s32 WXC_GetStateCode(void);
void ComRequest(u8 request); // C++ name _Z10ComRequesth

// StaffrollTask (0x02077810)
extern "C" void StaffrollTask(void);
ARM void StaffrollTask(void) {
    srStepTable[data_0212c500]();
}
