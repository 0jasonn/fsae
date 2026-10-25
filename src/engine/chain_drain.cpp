#include "engine/functions.h"
#include "engine/chain.h"
#include "global.h"
#include "types.h"

// Chain_Drain() (0x0200c500): takes the entries off the chain at data_021277d0 one by one, unlinking each before its
// callback is called with (arg, -1).
ARM void Chain_Drain(void) {
    ChainNode *node;
    void (*callback)(void *, s32);

    node = data_021277d0;
    while (node != NULL) {
        data_021277d0 = node->next;
        callback = (void (*)(void *, s32))node->callback;
        callback((void *)node->arg, -1);
        node = data_021277d0;
    }
}
