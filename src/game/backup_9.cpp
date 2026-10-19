#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"
#include "game/savemedia.h"

// Save media unit 9 (module backup). Address -> name (original names):
//   0x02056478 isAccordData

// First words of a save FAT header: two 16-bit checks and the 4-byte magic.
typedef struct SaveHeaderWords {
    u16 check0;
    u16 check1;
    u32 magic;
} SaveHeaderWords;

ARM s32 isAccordData(_SAVEHEADER *header, const u32 *data, s32 size) {
    SaveHeaderWords *words = (SaveHeaderWords *)header;
    u16 sum = CalcChecksum((const u16 *)&words->magic, 4) + CalcChecksum((const u16 *)data, size);

    if (words->check0 != sum || words->check1 != (u16)(0x10000 - sum) || words->magic != 0x54463453) {
        return 0;
    }
    return 1;
}
