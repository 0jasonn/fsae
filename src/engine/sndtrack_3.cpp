#include "engine/functions.h"
#include "global.h"
#include "engine/sndlist.h"
#include "engine/sndlink.h"
#include "engine/sndtrack.h"
#include "engine/sndvoice.h"

extern "C" {
u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32 saved);
extern SndList data_021848fc; // pending list that matched nodes are queued on
void SndPending_AppendLocked(u8 *node);
}

// SndTrack_ReleaseCounted: decrements the track's counter and releases its channel when the counter reaches zero.
extern "C" void SndTrack_ReleaseCounted(SndTrack *track);
ARM void SndTrack_ReleaseCounted(SndTrack *track) {
    if (track->counter == 0) {
        return;
    }
    track->counter = track->counter - 1;
    if (track->counter != 0) {
        return;
    }
    SndVoice_ReleaseChannel((SndVoice *)track);
}

// SndList_MoveMatching: with interrupts off, unlinks every node of the list whose key at +8 equals key and queues it on
// the pending list.
extern "C" void SndList_MoveMatching(SndList *list, s32 key);
ARM void SndList_MoveMatching(SndList *list, s32 key) {
    u32 irq;
    u8 *node;
    u8 *next;

    irq = OS_DisableInterrupts();
    node = func_020c2064(list, 0);
    if (node != 0) {
        do {
            next = func_020c2064(list, node);
            if (*(s32 *)(node + 8) == key) {
                func_020c2004(list, node);
                SndPending_AppendLocked(node);
            }
            node = next;
        } while (node != 0);
    }
    OS_RestoreInterrupts(irq);
}

// SndPending_AppendLocked: appends the node to the pending list with interrupts off.
extern "C" void SndPending_AppendLocked(u8 *node);
ARM void SndPending_AppendLocked(u8 *node) {
    u32 irq;

    irq = OS_DisableInterrupts();
    SndList_Append(&data_021848fc, node);
    OS_RestoreInterrupts(irq);
}
