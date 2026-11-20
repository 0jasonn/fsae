#include "engine/functions.h"
#include "engine/data_0212c564.h"
#include "global.h"
#include "ui/doorsel.h"
#include "engine/data_0212c500.h"

// Door select module (doorsel): DoorSelTask runs the current door select step (table data_020f25f0, indexed by the
// screen state data_0212c500).
//   DoorSelTask (0x0202a968)

extern void (*const data_020f25f0[])(void);

// DoorSelTask (0x0202a968): runs the current door select step, then the frame's shared update.
void DoorSelTask(void) {
    data_020f25f0[data_0212c500]();
    data_0212c564();
    func_020830ec();
}
