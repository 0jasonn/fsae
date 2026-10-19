#include "engine/functions.h"
#include "global.h"
#include "game/hitdecls.h"

// Background animation (module bganm). Original names from the debug build:
//   BgAnm, getanmcnt, SendBgAnmData, BgAnmInit, Set1BlockOshiYoyaku, Check1BlockOshiYoyaku

// One entry of the animation script: the records to send (w0) and the frame time, or the jump back count (w1).
typedef struct BgAnmEntry {
    u32 *records; // 0x00: pointer to the transfer records (SendBgAnmData)
    u32 time; // 0x04: time word, decoded by getanmcnt; the entry after the end of a loop holds the jump back count
} BgAnmEntry;

// One background animation slot (8 bytes, data_02134a68 holds 8 of them).
typedef struct BgAnmSlot {
    BgAnmEntry *cur; // 0x00: entry being played, NULL when the slot is idle
    u16 unk_04;
    u16 timer; // 0x06: frames left before the next entry
} BgAnmSlot;

extern BgAnmSlot data_02134a68[];
extern BgAnmEntry *data_020ce17c[]; // script table, indexed by the id in BgAnmInit's list
extern u32 data_020cd6b8[]; // per-id table of 16-bit time values (8 entries each) for random times
extern u8 data_0212c5ac; // non-zero while the screen is blanked: records are not sent

u16 getanmcnt(u32 *time);
void SendBgAnmData(u32 *records);

// Advances every active slot by one frame and loads the next entry when the timer runs out.
ARM void BgAnm(void) {
    u8 advanced;
    BgAnmSlot *slot;
    u16 count;

    advanced = 0;
    slot = data_02134a68;
    count = 9;
    count--;
    do {
        if (slot->cur == NULL) {
            break;
        }
        slot->timer--;
        if (slot->timer == 0) {
            if (advanced == 0) {
                if (data_0212c5ac == 0) {
                    SendBgAnmData(slot->cur->records);
                }
                slot->timer = getanmcnt(&slot->cur->time);
                slot->cur = slot->cur + 1;
                if (slot->cur->records == NULL) {
                    slot->cur = (BgAnmEntry *)((u8 *)slot->cur - (slot->cur->time << 3));
                }
                advanced = 1;
            } else {
                slot->timer++;
            }
        }
        slot++;
        count--;
    } while (count != 0);
    UpdateIroyuka();
}

// Frame time of a script entry: the low half-word, or for a random time (bit 31) one of the table values.
ARM u16 getanmcnt(u32 *time) {
    if ((*time & 0x80000000) == 0) {
        return (u16)*time;
    }
    return ((u16 *)data_020cd6b8[*time & 0xff])[Random() & 7];
}

// Sends the transfer records at a script entry (until the record with bit 31 clear): a character block to VRAM or a
// palette, depending on bit 28 of the first word.
ARM void SendBgAnmData(u32 *records) {
    u32 *rec;
    u8 *resource;
    s32 count;
    u32 low;

    rec = records;
    while (1) {
        resource = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), rec[1]);
        low = *(u16 *)rec;
        count = ((u8 *)rec)[2] + 1;
        if (((rec[0] >> 28) & 1) != 0) {
            CgPalletSet((u16 *)resource, low >> 5, count);
        } else {
            MIi_CpuCopyFast(resource, (void *)(low + 0x8000 + 0x6000000), count << 5);
        }
        if ((rec[0] >> 31) == 0) {
            break;
        }
        rec += 2;
    }
}

// Starts the animation slots from a list of script ids, ended by 0xffff.
ARM void BgAnmInit(u16 *ids) {
    BgAnmSlot *slot;
    BgAnmEntry *entry;
    u16 index;

    index = *ids;
    slot = data_02134a68;
    if (index == 0xffff) {
        return;
    }
    do {
        entry = data_020ce17c[index];
        slot->cur = entry;
        slot->timer = getanmcnt(&entry->time);
        ids++;
        index = *ids;
        slot++;
    } while (index != 0xffff);
}

// Sets the block at (a, b) with the block kind 0x401e when the cell kind is 0, 1, 2, 3 or 0x23.
ARM void Set1BlockOshiYoyaku(u16 a, u16 b) {
    int kind;

    kind = func_02083e54(func_02083ca8(a, b));
    if (kind != 2 && kind != 3 && kind != 1 && kind != 0x23) {
        return;
    }
    func_0208366c(0x401e, a, b);
}

// Whether the cell at (a, b) is of block kind 0x401e.
ARM BOOL Check1BlockOshiYoyaku(u16 a, u16 b) {
    return func_02083e54(func_02083ca8(a, b)) == 0x401e;
}
