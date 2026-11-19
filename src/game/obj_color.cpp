#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/objcolor.h"

typedef struct ResIDTranslate2 {
    s16 id;
    u16 value[5];
} ResIDTranslate2;

extern u8 set58_bodyState[];
extern u8 data_02134ae8[];
extern const u32 data_020dd8ec[];
extern const ResIDTranslate2 data_020cf8d4[];
void registOC(OC_CTRL_ *ctrl, u8 id, u8 count);
u16 GetResTranslateID2(u16 id, const ResIDTranslate2 *table, s32 count);

// GetObjColor (0x02027ec4): returns the first palette slot for colour index. A slot that already holds the colour is
// reused (reference count up); otherwise the first run of free records long enough for the colour (count from the
// table entry) is taken, and the colour's palette rows are loaded into the slot (the resource id is translated by game
// state; id 0x74 always goes to slot 0xc). Returns 0 when there is no room.
u32 GetObjColor(u8 index) {
    u8 count;
    u8 length;
    OC_CTRL_ *rec;
    u16 resId;
    u16 *palette;
    u32 row;
    u32 info;
    u8 slot = 0;
    rec = (OC_CTRL_ *)set58_bodyState;
    do {
        if (rec->id == index) {
            registOC(rec, index, rec->count);
            return slot;
        }
        slot++;
        rec++;
    } while ((u8 *)rec < data_02134ae8);
    info = data_020dd8ec[index];
    count = (info >> 24) & 0xf;
    row = ((info >> 28) & 0xf);
    slot = 0;
    rec = (OC_CTRL_ *)set58_bodyState;
    do {
        if (rec->refCount == 0) {
            for (length = 0; length < count; length++) {
                if (rec[length].refCount != 0) {
                    break;
                }
            }
            if (length == count) {
                registOC(rec, index, count);
                resId = GetResTranslateID2(info & 0xffffff, data_020cf8d4, 6);
                palette = (u16 *)KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), resId);
                if (resId == 0x74) {
                    slot = 0xc;
                }
                CgPalletSet(palette + row * 16, slot + 0x10, count);
                return slot;
            }
        }
        slot++;
        rec++;
    } while ((u8 *)rec < data_02134ae8);
    return 0;
}
