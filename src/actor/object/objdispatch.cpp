#include "engine/functions.h"
#include "global.h"
#include "actor/object/objdispatch.h"
#include "engine/entity.h"
#include "actor/object/objdispatch_api.h"

// Generic object dispatch, 0x02076b24. Runs the entry of data_02116588 for the object's id, then clears the contact
// flag bit 0x80 that the update has just used.
void objDispatchClearContact(Entity *e) {
    data_02116588[e->objId](e);
    e->contactFlags = e->contactFlags & 0x7f;
}

// Second unit of the object dispatch module (objdispatch.cpp has objDispatchClearContact, 0x02076b24).
//   objDispatchPutWork (0x02076b50): returns the work to the pool (tail call to PutObjWork).
//   objDispatchAction (0x02076b5c): runs the action of data_021166f0 for the object, then the shared update.

extern const EntityFunc data_021166f0[]; // action table by e->action (shield, staffroll and stage select states)
extern u8 data_0212c4b8;                 // global pause flag, the actions are skipped while it is set

// Fields of the dispatch that live in the object's Entity::unk_64 array
typedef struct ObjDispatchVars {
    u8 unk_00[0x65];
    u8 delayTimer; // 0x65, counts down to 0 while the action runs (meaning not known yet)
} ObjDispatchVars;

// objDispatchPutWork (0x02076b50)
void objDispatchPutWork(Entity *e) {
    PutObjWork(e);
}

// objDispatchAction (0x02076b5c)
void objDispatchAction(Entity *e) {
    if (e->action != 0) {
        if (data_0212c4b8 == 0) {
            if (VARS(ObjDispatchVars, e)->delayTimer != 0) {
                VARS(ObjDispatchVars, e)->delayTimer--;
            }
            data_021166f0[e->action](e);
            if (e->iframes != 0) {
                if ((s8)e->iframes > 0) {
                    e->iframes--;
                } else {
                    e->iframes++;
                }
            }
        }
    } else {
        data_021166f0[e->action](e);
    }
    func_020857c8(e);
}
