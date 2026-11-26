#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/pm/pm.h"

// Entries are added to the callback list at data_0212b93c in front (priority -255) or to the list at data_0212b924 at the
// end (priority 255); WBT_MpChildSendHook inserts into the list at data_0212b93c with a caller-chosen priority.
void PM_PrependPostExitCallback(void *item) {
    PMi_InsertList(&data_0212b93c, item, -255, 1);
}

void PM_AppendPostExitCallback(void *item) {
    PMi_InsertList(&data_0212b924, item, 255, 0);
}

void WBT_MpChildSendHook(void *item, s32 priority) {
    PMi_InsertList(&data_0212b93c, item, priority, 0);
}
