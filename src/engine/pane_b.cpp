#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// pane_b: functions Pane_visitNoop, Pane_getClassInfo (0x020b5840 to 0x020b5844), all matching.

// Pane_visitNoop(self, arg) (0x020b5840, provisional name): visit of the Pane, does nothing
extern "C" void Pane_visitNoop(Pane *self, void *arg);
ARM void Pane_visitNoop(Pane *self, void *arg) {
}

// Pane_getClassInfo() (0x020b5844, provisional name): vtable slot 0 of Pane, returns the class info of Pane
extern "C" void *Pane_getClassInfo(void);
ARM void *Pane_getClassInfo(void) {
    return data_02126a60;
}
