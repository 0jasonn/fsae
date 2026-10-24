#include "engine/functions.h"
#include "global.h"
#include "game/fileselui.h"

// Functions in this file (no debug names; the controller is data_0217e6f0):
//   subTask_fileSel_init (0x020adac0): subTask_fileSel_init, calls fileSelUIViewCtrl::initialize on the controller
//   subTask_fileSel_end (0x020adad4): subTask_fileSel_end, calls fileSelUIViewCtrl::finalize on the controller
//   subTask_fileSel (0x020adae8): subTask_fileSel, calls fileSelUIViewCtrl::update on the controller
//   subTask_fileSel_noopA (0x020adafc), subTask_fileSel_noopB (0x020adb00): empty callbacks

// subTask_fileSel_init (0x020adac0)
ARM void subTask_fileSel_init(void) {
    fileSelUIViewCtrl_initialize((FileSelUIViewCtrl *)data_0217e6f0);
}

// subTask_fileSel_end (0x020adad4)
ARM void subTask_fileSel_end(void) {
    fileSelUIViewCtrl_finalize((FileSelUIViewCtrl *)data_0217e6f0);
}

// subTask_fileSel (0x020adae8)
ARM void subTask_fileSel(void) {
    fileSelUIViewCtrl_update((FileSelUIViewCtrl *)data_0217e6f0);
}

// subTask_fileSel_noopA (0x020adafc)
ARM void subTask_fileSel_noopA(void) {
}

// subTask_fileSel_noopB (0x020adb00)
ARM void subTask_fileSel_noopB(void) {
}
