#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "enemy/decls_b2.h"

// Functions in this file (module dataload, original names from the debug build): DataLoad (DataLoad(unsigned short))
//
// The entry list at data_0210392c[index] holds 12-byte entries {key, dest, flags}. The key carries the resource id in
// its low 24 bits and the kind in bits 24..27; bit 31 of flags marks LZ compressed data, and bit 7 of the key's high
// byte continues the list. Kinds 10..15 are tested against the flag byte data_021348d8.

typedef struct DataLoadEntry {
    u32 key;
    u32 dest;
    u32 flags;
} DataLoadEntry;

extern const u32 data_0210392c[];
extern const u16 data_020cf924[];
extern const u16 data_020cf948[];
extern u8 data_021348d8;

// DataLoad (0x02029fe8)
ARM void DataLoad(u16 index) {
    DataLoadEntry *entry = (DataLoadEntry *)data_0210392c[index];
    u32 kind;
    u32 send;
    u32 id;
    u32 row;
    u32 state;
    u32 size;
    u32 key;
    u32 dest;
    u32 flags;
    void *app;
    void *src;

    for (;;) {
        send = 0;
        kind = (entry->key >> 24) & 0xf;
        switch (kind) {
        case 13:
            return;
        case 14:
            if (data_021348d8 >= 1) {
                send = 1;
            }
            break;
        case 15:
            if (data_021348d8 != 0) {
                send = 1;
            }
            break;
        case 10:
            send = 1;
            break;
        default:
            if (kind == data_021348d8) {
                send = 1;
            }
            break;
        }

        if (send != 0) {
            id = entry->key & 0xffffff;
            state = data_0212c7c8[0x8e];
            if (state >= 6) {
                for (row = 0; row < 0x19; row += 5) {
                    if (id == data_020cf948[row]) {
                        id = data_020cf948[row + state - 5];
                        break;
                    }
                }
            } else {
                id = GetResTranslateID((u16)id, data_020cf924, 3);
            }
            app = KnifeApp_getInstance();
            src = KnifeApp_getZeldaResource_08dde0(app, (s32 *)&size, id);
            dest = entry->dest;
            flags = entry->flags;
            if (flags & 0x80000000) {
                MI_UncompressLZ16(src, (void *)dest, flags);
            } else {
                MIi_CpuCopy16(src, (void *)dest, flags);
            }
        }

        key = entry->key;
        entry++;
        if (((key >> 24) & 0x80) == 0) {
            break;
        }
    }
}
