#include "engine/functions.h"
#include "global.h"

extern "C" void func_020c2004(void *list, void *node);
extern "C" void *SndRangeTree_ParentList(u8 *node);

// Removes a node from the child list that holds it (the list is found through the node's range tree position).
extern "C" void SndRangeTree_Remove(u8 *node);
ARM void SndRangeTree_Remove(u8 *node) {
    func_020c2004(SndRangeTree_ParentList(node), node);
}

// Stores two words for the node src: the first is src minus a 7-bit offset (bits 8..14 of the halfword at +2), the second
// is the word at +4 plus the address of src + 0x10.
extern "C" void SndRangeTree_DecodeBounds(u32 *out, u8 *src);
ARM void SndRangeTree_DecodeBounds(u32 *out, u8 *src) {
    u16 offset;
    u32 base;

    offset = (*(u16 *)(src + 2) >> 8) & 0x7f;
    base = (u32)src + 0x10;
    out[0] = (u32)src - offset;
    out[1] = *(u32 *)(src + 4) + base;
}

// Unlinks a node from a list whose first and last words are at +0 and +4. The links are prev at node +8 and next at
// node +0xc. Returns the previous node.
struct RangeChildList {
    u8 *first;
    u8 *last;
};
extern "C" u8 *SndRangeTree_UnlinkChild(RangeChildList *list, u8 *node);
ARM u8 *SndRangeTree_UnlinkChild(RangeChildList *list, u8 *node) {
    u8 *prev;
    u8 *next;

    prev = *(u8 **)(node + 0x8);
    next = *(u8 **)(node + 0xc);
    if (prev != 0) {
        *(u8 **)(prev + 0xc) = next;
    } else {
        list->first = next;
    }
    if (next != 0) {
        *(u8 **)(next + 0x8) = prev;
    } else {
        list->last = prev;
    }
    return prev;
}

// Links a node after ref in the child list (at the head when ref is null). Returns the node.
extern "C" u8 *SndRangeTree_InsertChild(RangeChildList *list, u8 *node, u8 *ref);
ARM u8 *SndRangeTree_InsertChild(RangeChildList *list, u8 *node, u8 *ref) {
    u8 *next;

    *(u8 **)(node + 0x8) = ref;
    if (ref != 0) {
        next = *(u8 **)(ref + 0xc);
        *(u8 **)(ref + 0xc) = node;
    } else {
        next = list->first;
        list->first = node;
    }
    *(u8 **)(node + 0xc) = next;
    if (next != 0) {
        *(u8 **)(next + 0x8) = node;
    } else {
        list->last = node;
    }
    return node;
}

// Initialises a node at the buffer's current position: key at +0, a zero halfword at +2, the size (end minus the
// node's data start) at +4, and zero links at +8 and +0xc. Returns the node.
struct RangeBuffer {
    u8 *cur;
    u32 end;
};
extern "C" u8 *SndRangeTree_InitNode(RangeBuffer *buf, u16 key);
ARM u8 *SndRangeTree_InitNode(RangeBuffer *buf, u16 key) {
    u8 *node;
    u32 end;
    u32 zero;

    node = buf->cur;
    end = buf->end;
    *(u16 *)node = key;
    zero = 0;
    *(u16 *)(node + 2) = zero;
    *(u32 *)(node + 4) = end - (u32)(node + 0x10);
    *(u32 *)(node + 8) = zero;
    *(u32 *)(node + 0xc) = zero;
    return node;
}
