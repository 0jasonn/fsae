#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"
#include "game/savemedia.h"

// Save media unit 9 (module backup). Address -> name (original names):
//   0x02056478 isAccordData, 0x020564e4 checkFatData

// First words of a save FAT header: two 16-bit checks and the 4-byte magic.
typedef struct SaveHeaderWords {
    u16 check0;
    u16 check1;
    u32 magic;
} SaveHeaderWords;

s32 isAccordData(_SAVEHEADER *header, const u32 *data, s32 size) {
    SaveHeaderWords *words = (SaveHeaderWords *)header;
    u16 sum = CalcChecksum((const u16 *)&words->magic, 4) + CalcChecksum((const u16 *)data, size);

    if (words->check0 != sum || words->check1 != (u16)(0x10000 - sum) || words->magic != 0x54463453) {
        return 0;
    }
    return 1;
}

s32 checkFatData(_SAVEHEADER *header) {
    SaveHeaderWords *words = (SaveHeaderWords *)header;

    if (words->magic == 0x466c6544) { // "DelF"
        goto checkAnd;
    }
    if (words->magic == 0x54463453) { // "S4FT"
        goto checkSum;
    }
    if (words->magic == 0x54494e49) { // "INIT"
        goto checkAnd;
    }
    goto invalid;

checkSum:
    return (words->check0 + words->check1 != 0x10000) ? 0 : 2;
checkAnd:
    return (words->check0 & words->check1) == 0xffff ? 1 : 0;
invalid:
    return 0;
}
