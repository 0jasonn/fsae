#include "engine/functions.h"
#include "global.h"
#include "engine/misc.h"
#include "engine/data_0212c500.h"

#include "engine/palette_buff.h"
#include "game/keyread.h"
extern u8 data_0212c4b8;
extern u8 data_0212c4d4;
extern u16 data_0212c520;


extern u16 scrollArgs[];
extern u8 objAffineSetAlt[];
extern u8 data_0212c4e4;
extern u16 data_0212c510;
extern Entity *data_0212c534;
extern u16 playerKeysPrev[];
extern u8 plScratchBuffer[];
extern const EntityFunc entityDispatchTable[];


extern const u32 data_021186e4[];

extern const s8 *const data_0211525c[];

extern const VoidFunc rankingStepTable[];



void RankingTask(void) {
    rankingStepTable[data_0212c500]();
}
