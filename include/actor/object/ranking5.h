#ifndef ACTOR_OBJECT_RANKING5_H
#define ACTOR_OBJECT_RANKING5_H

#include "engine/functions.h"
#include "game/rankingsave.h"

// Shared with other files, declared here until functions.h gets them.
extern u8 rankingStepTable[];    // 0x02115268, the ranking step table (rankingStepTable)
extern const u8 data_02115298[]; // template of the 0x38-byte message screen record copied by ranking_exit

// One ranking table entry (4 bytes), data_02171d00[player count]. ranking_getKey reads the rank byte.
typedef struct RankingEntry {
    /* 00 */ u8 playerIndex;
    /* 01 */ u8 rank; // 0 for the best score, equal scores share a rank
    /* 02 */ u16 score;
} RankingEntry;
extern RankingEntry data_02171d00[];

// C++ linkage, as in the original
void ranking_exit(void);          // 0x02055d28, original name ranking_exit()
s32 Save4Swords(u8 slot);         // 0x020490d8, original name Save4Swords(unsigned char)

#endif
