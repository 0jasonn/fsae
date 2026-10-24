#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (module knife, original names from the debug build): Knife_DataLoad_Tbl_Init (Knife_DataLoad_Tbl_Init())

// One entry of the data load tables: the key holds the resource id in its low 24 bits and a continuation flag in bit 31
typedef struct KnifeDataLoadEntry {
    u32 key;
    u32 unk_04;
    s32 data; // resource size, filled in from the resource when it is 0
} KnifeDataLoadEntry;

extern KnifeDataLoadEntry *data_0210392c[]; // 0x2b table heads

// Knife_DataLoad_Tbl_Init (0x02029f10): for each table head, fills in the missing sizes of its entries. The entries of
// one table continue while bit 31 of the key is set.
ARM void Knife_DataLoad_Tbl_Init(void) {
    u32 i;
    KnifeDataLoadEntry *entry;
    u32 more;
    s32 size;

    for (i = 0; i < 0x2b; i++) {
        entry = data_0210392c[i];
        if (entry != NULL) {
            do {
                more = (entry->key >> 24) & 0x80;
                if (entry->data == 0) {
                    KnifeApp_getZeldaResource_08dde0(KnifeApp_getInstance(), &size, entry->key & 0xffffff);
                    entry->data = size;
                }
                entry++;
            } while (more != 0);
        }
    }
}

// One entry of the objvram table: the key (resource id in the low 24 bits, continuation flag in bit 31) and the size
typedef struct KnifeObjVramEntry {
    u32 key;
    s32 size; // filled in from the resource when it is 0
} KnifeObjVramEntry;

extern KnifeObjVramEntry *vgroupRequestTable[]; // 0x92 table heads

// Knife_objvram_init (0x02029f7c): the same as Knife_DataLoad_Tbl_Init for the 0x92 objvram tables of 8-byte entries.
ARM void Knife_objvram_init(void) {
    u32 i;
    KnifeObjVramEntry *entry;
    u32 key;
    s32 size;

    for (i = 0; i < 0x92; i++) {
        entry = vgroupRequestTable[i];
        if (entry != NULL) {
            do {
                key = entry->key;
                if (entry->size == 0) {
                    KnifeApp_getZeldaResource_08dde0(KnifeApp_getInstance(), &size, key & 0xffffff);
                    entry->size = size;
                }
                entry++;
            } while ((key & 0x80000000) != 0);
        }
    }
}
