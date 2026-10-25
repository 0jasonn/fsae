#ifndef WIP_A_NODE_H
#define WIP_A_NODE_H

#include "global.h"
#include "types.h"

// Source block: the text pointer at +0, a word at +4, a word at +8 and the record base at +0x18.
typedef struct NodeSrc {
    u8 *text;
    u32 value;
    u32 extra;
    u8 unk_0c[0xc];
    u8 *base;
} NodeSrc;

// Record written at base + offset: four words, and a count or pointer at +0xc, a value at +0x10.
typedef struct NodeRec {
    u32 w0;
    u8 *text;
    u32 w8;
    u32 wC;
    u32 w10;
    u32 w14;
} NodeRec;

#endif
