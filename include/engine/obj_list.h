#ifndef ENGINE_OBJ_LIST_H
#define ENGINE_OBJ_LIST_H

#include "types.h"

// Node of the intrusive entity lists: the links sit at the start of every Entity (Entity unk_00[8]), and the list heads
// are bare nodes. Each list is circular and its head points at itself when empty.
typedef struct EntityNode {
    struct EntityNode *prev;
    struct EntityNode *next;
} EntityNode;

// The 8 object list heads, one per object group (0x0212c6b0..0x0212c6f0, followed by data_0212c6f0, a DisplayState).
// The symbols data_0212c6b8, data_0212c6c0 and data_0212c6d0 are heads 1, 2 and 4 of this array.
extern EntityNode data_0212c6b0[8];
extern EntityNode *data_0212c52c;   // node being updated by ObjMove; PutObjWork steps it back when it unlinks that node

#endif
