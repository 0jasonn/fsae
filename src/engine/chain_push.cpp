#include "engine/functions.h"
#include "engine/chain.h"
#include "global.h"
#include "types.h"

// Chain_Push(a, b, node) (0x0200c574): links node in front of the chain at data_021277d0. The first argument goes to
// the arg word and the second to the callback word of the node.
ARM void Chain_Push(u32 a, u32 b, ChainNode *node) {
    node->next = data_021277d0;
    node->callback = b;
    node->arg = a;
    data_021277d0 = node;
}
