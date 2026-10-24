#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (module objcolor, original names from the debug build):
//   InitObjColor, GetResTranslateID2 (GetResTranslateID2(unsigned short, ResIDTranslate2 const*, long)), registOC,
//   GetObjColor, PutObjColor

// One record of the object colour table at set58_bodyState: 16 records of 4 bytes. refCount counts the users of the
// slot, id is the colour id it holds (0xff when empty) and count is the number of slots the colour takes.
typedef struct OC_CTRL_ {
    u8 refCount;
    u8 id;
    u8 count;
    u8 unk_3;
} OC_CTRL_;

// Translation of a resource id by the game state (one entry of data_020cf8d4 per id; value[] for states 1..5)
typedef struct ResIDTranslate2 {
    s16 id;
    u16 value[5];
} ResIDTranslate2;

extern u8 set58_bodyState[];
extern u8 data_02134ae8[];
extern u8 data_02134ad4[];
extern u8 data_02134ae4[];
extern u8 data_0212c7c8[];
extern const u32 data_020dd8ec[];
extern const ResIDTranslate2 data_020cf8d4[];

// InitObjColor (0x02027dc4): empties the records (refCount 0xff, id 0xff, count 0), then clears refCount and id of the
// records from data_02134ad4 to data_02134ae4.
ARM void InitObjColor(void) {
    OC_CTRL_ *rec;

    rec = (OC_CTRL_ *)set58_bodyState;
    do {
        rec->refCount = 0xff;
        rec->id = 0xff;
        rec->count = 0;
        rec++;
    } while ((u8 *)rec < data_02134ae8);

    rec = (OC_CTRL_ *)data_02134ad4;
    do {
        rec->id = 0;
        rec->refCount = 0;
        rec++;
    } while ((u8 *)rec < data_02134ae4);
}

// GetResTranslateID2 (0x02027e1c): finds id in the table and returns its value for the current game state (byte 0x8e
// of data_0212c7c8). Returns id itself when it is not in the table or the state is not 1..5.
ARM u16 GetResTranslateID2(u16 id, const ResIDTranslate2 *table, s32 count) {
    const ResIDTranslate2 *entry;
    s32 i;
    u8 state;

    for (i = 0; i < count; i++) {
        entry = &table[i];
        if (id == entry->id) {
            state = data_0212c7c8[0x8e];
            if (state == 1) {
                return entry->value[0];
            }
            if (state == 2) {
                return entry->value[1];
            }
            if (state == 3) {
                return entry->value[2];
            }
            if (state == 4) {
                return entry->value[3];
            }
            if (state == 5) {
                return entry->value[4];
            }
            return id;
        }
    }
    return id;
}

// registOC (0x02027e9c): takes count consecutive records starting at ctrl for the colour id. Each record gets refCount + 1,
// the id and the count it has left (count down to 1).
ARM void registOC(OC_CTRL_ *ctrl, u8 id, u8 count) {
    u8 remaining;

    remaining = count;
    do {
        ctrl->refCount += 1;
        ctrl->id = id;
        ctrl->count = remaining;
        ctrl++;
        remaining -= 1;
    } while (remaining != 0);
}
