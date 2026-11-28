#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/dc_cache.h"
#include "sdk/snd/mutex_wrap_api.h"
#include "sdk/snd/snd_bank.h"

// SND_AssignWaveArc(bank, slot, waveArc) (0x0201ba78): makes slot of the bank use waveArc, first removing the slot from
// the list of the archive it used before.
void SND_AssignWaveArc(SndBank *bank, s32 slot, SndWaveArc *waveArc) {
    SndWaveArc *oldArc;
    SndWaveArcLink *link;
    SndWaveArcLink *prev;

    Mutex_LockGlobal();
    oldArc = bank->waveArcLink[slot].waveArc;
    if (oldArc != NULL) {
        if (waveArc == oldArc) {
            Mutex_UnlockGlobal();
            return;
        }
        prev = oldArc->topLink;
        if (&bank->waveArcLink[slot] == prev) {
            oldArc->topLink = bank->waveArcLink[slot].next;
            DC_StoreRange(bank->waveArcLink[slot].waveArc, 0x3c);
        } else {
            while (prev != NULL) {
                link = prev->next;
                if (&bank->waveArcLink[slot] == link) {
                    break;
                }
                prev = link;
            }
            prev->next = bank->waveArcLink[slot].next;
            DC_StoreRange(prev, 8);
        }
    }
    link = waveArc->topLink;
    waveArc->topLink = &bank->waveArcLink[slot];
    bank->waveArcLink[slot].next = link;
    bank->waveArcLink[slot].waveArc = waveArc;
    Mutex_UnlockGlobal();
    DC_StoreRange(bank, 0x3c);
    DC_StoreRange(waveArc, 0x3c);
}

// SND_DestroyBank(bank) (0x0201bb48): removes all four wave archive slots of the bank from the lists of the archives
// that use them.
void SND_DestroyBank(SndBank *bank) {
    s32 i;
    SndWaveArc *waveArc;
    SndWaveArcLink *link;
    SndWaveArcLink *next;

    Mutex_LockGlobal();
    for (i = 0; i < 4; i++) {
        waveArc = bank->waveArcLink[i].waveArc;
        if (waveArc == NULL) {
            continue;
        }
        link = waveArc->topLink;
        if (&bank->waveArcLink[i] == link) {
            waveArc->topLink = bank->waveArcLink[i].next;
            DC_StoreRange(waveArc, 0x3c);
        } else {
            while (link != NULL) {
                next = link->next;
                if (&bank->waveArcLink[i] == next) {
                    break;
                }
                link = next;
            }
            link->next = bank->waveArcLink[i].next;
            DC_StoreRange(link, 8);
        }
    }
    Mutex_UnlockGlobal();
}

// SND_DestroyWaveArc(waveArc) (0x0201bbe0): detaches every bank slot that uses the archive.
void SND_DestroyWaveArc(SndWaveArc *waveArc) {
    SndWaveArcLink *link;
    SndWaveArcLink *next;

    Mutex_LockGlobal();
    link = waveArc->topLink;
    if (link != NULL) {
        do {
            next = link->next;
            link->waveArc = NULL;
            link->next = NULL;
            DC_StoreRange(link, 8);
            link = next;
        } while (link != NULL);
    }
    Mutex_UnlockGlobal();
}
