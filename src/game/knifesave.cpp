#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (module com, original names from the debug build): setKnifeSaveData4S
// (setKnifeSaveData4S(unsigned char, unsigned long, unsigned long, unsigned char))

// One save slot of enemyTypeFlags: two words
typedef struct KnifeSaveWords {
    u32 a;
    u32 b;
} KnifeSaveWords;

extern KnifeSaveWords enemyTypeFlags[]; // one pair per save slot
extern u8 data_0212c858[];  // one byte per save slot, at slot * 4

// setKnifeSaveData4S (0x020284d4): stores the two words of save slot index and the byte c of its entry.
ARM void setKnifeSaveData4S(u8 index, u32 a, u32 b, u8 c) {
    KnifeSaveWords *slot;

    enemyTypeFlags[index].a = a;
    slot = &enemyTypeFlags[index];
    slot->b = b;
    data_0212c858[index * 4] = c;
}
