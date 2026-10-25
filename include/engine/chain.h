#ifndef WIP_A_CHAIN_H
#define WIP_A_CHAIN_H

#include "global.h"
#include "types.h"

// Entry of the global chain whose head is data_021277d0: next entry, a callback and the argument it is called with.
typedef struct ChainNode {
    struct ChainNode *next;
    u32 callback;
    u32 arg;
} ChainNode;

extern ChainNode *data_021277d0;

extern "C" void Chain_Push(u32 a, u32 b, ChainNode *node);
extern "C" void Chain_Drain(void);

#endif
