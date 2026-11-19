#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (module disp, original names from the debug build):
//   DispCtrlClear (DispCtrlClear()), AssignObj (AssignObj(void*))

#include "engine/display_state.h"
extern u8 data_0212f890[];    // start of the object range of AssignObj
extern u8 data_02134890[];    // end of the object range of AssignObj

// DispCtrlClear (0x0202a700): clears the display block data_0212c568 points to and sets its displayFlags to 0x40.
void DispCtrlClear(void) {
    MemClearFast(data_0212c568, sizeof(DisplayState));
    data_0212c568->displayFlags = 0x40;
}

// AssignObj (0x0202a728): 1 when the pointer lies in the object range data_0212f890 .. data_02134890, otherwise 0.
int AssignObj(void *ptr) {
    if ((u8 *)ptr >= data_0212f890 && (u8 *)ptr < data_02134890) {
        return 1;
    }
    return 0;
}
