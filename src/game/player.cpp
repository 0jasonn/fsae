#include "engine/functions.h"
#include "global.h"
#include "engine/misc_d.h"

// data_02134980 is the pause state block: [0] phase, [1] chosen pause option, [2] delay timer,
// [0xe] reset flag, [0xf] set when the wireless session is being closed

extern u8 data_02134980[];
extern u16 data_021355a0;
extern u16 data_0212c58c[];
extern u8 data_0212c4b8;
extern u8 data_0212c4d4;
extern u16 data_0212c520;


#include "game/pl.h"

#define PL_ARR (*(PlWork (*)[4])data_0212ceb0)

extern u16 data_0212c574[];
extern u8 data_0212dd90[];
extern u8 data_0212e190[];
extern u8 data_0212c4e4;
extern u16 data_0212c514;
extern u16 data_0212c510;
extern Entity *data_0212c534;
extern u16 data_0212c584[];
extern u8 data_0212c868[];
extern const EntityFunc data_02115258[];


extern u8 data_0217d36c[];
extern const u32 data_021186e4[];
extern const u8 data_0212c84c[];

extern const s8 *const data_0211525c[];

extern const VoidFunc data_02115268[];
extern u8 data_0212c504;



ARM void BindPlayers(void) {
    u8 i;

    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        BindPlayer(i);
    }
    data_0212c5bc[0x13] = 1;
}

ARM void WarpPlayer(void) {
    u8 i;

    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        PL_ARR[i].entity->action = 0x14;
        PL_ARR[i].entity->subAction = 0;
    }
}
