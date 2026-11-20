#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/pm/pmlist_wrap.h"

extern u8 data_0212b924[];
extern u8 data_0212b93c[];

// Removes an item from one of the two power management lists. The item arrives in r0 and goes to r1 for
// PMi_DeleteList, with the list head as r0.
extern "C" void PmList_DeleteSecond(void *item);

void PmList_DeleteFirst(void *item) {
    PMi_DeleteList(data_0212b93c, item);
}

void PmList_DeleteSecond(void *item) {
    PMi_DeleteList(data_0212b924, item);
}
