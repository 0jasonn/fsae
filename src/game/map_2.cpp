#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/decls_a.h"

// Map loader (module map, second unit). Original name from the debug build: MapLoad(unsigned long*, unsigned char).

#define REG_DISPSTAT (*(volatile u16 *)0x04000004)

extern u8 data_02163fa8[];
extern u8 data_02165fa8[];

// Loads the map resource list, one 12-byte entry at a time, waiting for each VBlank. Entry: { id (bit 31 = another entry
// follows), destination, flags (bit 31 = LZ compressed) }. A zero destination loads a character graphic (CgLoad) instead.
ARM void MapLoad(u32 *entries, u8 mode) {
    u32 *entry;
    void *src;

    if (mode == 0) {
        func_02029a50(data_02163fa8, 0x2000);
        func_02029a50(data_02165fa8, 0x1000);
    }
    entry = entries;
    do {
        while ((REG_DISPSTAT & 1) == 0) {
        }
        if (entry[1] != 0) {
            src = (void *)KnifeApp_getZelmapResource(KnifeApp_getInstance(), entry[0] & 0x7fffffff);
            if (KnifeApp_getZelmapResource(KnifeApp_getInstance(), entry[2]) & 0x80000000) {
                if ((s32)entry >= 0x6800000 && (s32)entry > 0x068a4000) {
                    MI_UncompressLZ16(src, (void *)entry[1]);
                } else {
                    MI_UncompressLZ8(src, (void *)entry[1]);
                }
            } else {
                MIi_CpuCopy16(src, (void *)entry[1], KnifeApp_getZelmapResource(KnifeApp_getInstance(), entry[2]));
            }
        } else {
            CgLoad(entry[0] & 0xffff);
        }
        entry += 3;
    } while (entry[-3] & 0x80000000);
}
