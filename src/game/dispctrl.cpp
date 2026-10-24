#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (module disp, original names from the debug build):
//   DispCtrlClear (DispCtrlClear()), AssignObj (AssignObj(void*))

extern void *data_0212c568;   // pointer to the 0x6c-byte block cleared by DispCtrlClear, its first halfword is set to 0x40
extern u8 data_0212f890[];    // start of the object range of AssignObj
extern u8 data_02134890[];    // end of the object range of AssignObj

// DispCtrlClear (0x0202a700): clears the 0x6c-byte block and sets its first halfword to 0x40.
ARM void DispCtrlClear(void) {
    func_02029a50(data_0212c568, 0x6c);
    *(u16 *)data_0212c568 = 0x40;
}

// AssignObj (0x0202a728): 1 when the pointer lies in the object range data_0212f890 .. data_02134890, otherwise 0.
ARM int AssignObj(void *ptr) {
    if ((u8 *)ptr >= data_0212f890 && (u8 *)ptr < data_02134890) {
        return 1;
    }
    return 0;
}
