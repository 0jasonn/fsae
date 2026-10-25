#include "engine/functions.h"
#include "global.h"

// Object list search (module objfind): data_0212c6b0 holds one circular list head per object group (8 bytes each,
// the list runs through next at +4) and data_0212c6f0 is the end of the heads.
//   getNumberOfObj (0x020774cc), findObj (0x0207752c).
// The objects are Entity works: objKind at +8 and objId at +9 are the search keys.

typedef struct ObjListNode {
    struct ObjListNode *prev; // 00
    struct ObjListNode *next; // 04
    u8 objKind;               // 08
    u8 objId;                 // 09
} ObjListNode;

typedef struct ObjListHead {
    ObjListNode *prev; // 00
    ObjListNode *next; // 04
} ObjListHead;

extern ObjListHead data_0212c6b0[];
extern ObjListHead data_0212c6f0[];

// getNumberOfObj (0x020774cc): number of objects with the given kind and id
extern "C" int getNumberOfObj(u8 kind, u8 id);
ARM int getNumberOfObj(u8 kind, u8 id) {
    int count;
    ObjListHead *head;
    ObjListNode *node;

    count = 0;
    for (head = data_0212c6b0; head < data_0212c6f0; head++) {
        for (node = head->next; node != (ObjListNode *)head; node = node->next) {
            if (node->objKind == kind && node->objId == id) {
                count++;
            }
        }
    }
    return count;
}

// findObj (0x0207752c): the first object with the given kind and id, or NULL
extern "C" Entity *findObj(u8 kind, u8 id);
ARM Entity *findObj(u8 kind, u8 id) {
    ObjListHead *head;
    ObjListNode *node;

    for (head = data_0212c6b0; head < data_0212c6f0; head++) {
        for (node = head->next; node != (ObjListNode *)head; node = node->next) {
            if (node->objKind == kind && node->objId == id) {
                return (Entity *)node;
            }
        }
    }
    return NULL;
}
