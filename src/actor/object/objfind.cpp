#include "engine/functions.h"
#include "global.h"
#include "actor/object/objfind_api.h"

// Object list search (module objfind): data_0212c6b0 holds one circular list head per object group (8 bytes each,
// the list runs through next at +4); the 8 heads end at data_0212c6f0 (a DisplayState).
//   getNumberOfObj (0x020774cc), findObj (0x0207752c).
// The objects are Entity works: objKind at +8 and objId at +9 are the search keys.

#include "engine/obj_list.h"

// getNumberOfObj (0x020774cc): number of objects with the given kind and id
int getNumberOfObj(u8 kind, u8 id) {
    int count;
    EntityNode *head;
    EntityNode *node;

    count = 0;
    for (head = data_0212c6b0; head < data_0212c6b0 + 8; head++) {
        for (node = head->next; node != head; node = node->next) {
            if (((Entity *)node)->objKind == kind && ((Entity *)node)->objId == id) {
                count++;
            }
        }
    }
    return count;
}

// findObj (0x0207752c): the first object with the given kind and id, or NULL
Entity *findObj(u8 kind, u8 id) {
    EntityNode *head;
    EntityNode *node;

    for (head = data_0212c6b0; head < data_0212c6b0 + 8; head++) {
        for (node = head->next; node != head; node = node->next) {
            if (((Entity *)node)->objKind == kind && ((Entity *)node)->objId == id) {
                return (Entity *)node;
            }
        }
    }
    return NULL;
}
