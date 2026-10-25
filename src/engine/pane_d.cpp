#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/pane.h"

// pane_d: functions Pane_releaseItemNoop (0x020b5ba4 to 0x020b5ba4), all matching.

// Pane_releaseItemNoop(item, heap) (0x020b5ba4, provisional name): release callback of an item, does nothing
extern "C" void Pane_releaseItemNoop(void *item, void *heap);
ARM void Pane_releaseItemNoop(void *item, void *heap) {
}
