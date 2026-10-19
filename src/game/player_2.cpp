#include "engine/functions.h"
#include "global.h"
#include "engine/misc_d.h"

// pauseState is the pause state block: [0] phase, [1] chosen pause option, [2] delay timer,
// [0xe] reset flag, [0xf] set when the wireless session is being closed

extern u8 pauseState[];
extern u16 data_021355a0;
extern u16 data_0212c58c[];
extern u8 data_0212c4b8;
extern u8 data_0212c4d4;
extern u16 data_0212c520;


#include "game/pl.h"

#define PL_ARR (*(PlWork (*)[4])data_0212ceb0)

extern u16 scrollArgs[];
extern u8 objAffineSet[];
extern u8 objAffineSetAlt[];
extern u8 data_0212c4e4;
extern u16 data_0212c514;
extern u16 data_0212c510;
extern Entity *data_0212c534;
extern u16 data_0212c584[];
extern u8 plScratchBuffer[];
extern const EntityFunc entityDispatchTable[];


extern u8 telopRequest[];
extern const u32 data_021186e4[];
extern const u8 data_0212c84c[];

extern const s8 *const data_0211525c[];

extern const VoidFunc rankingStepTable[];
extern u8 localPlayerIndex;



ARM void PlWorkReset(void) {
    PlWork *end;
    PlWork *plWork;

    plWork = PL_ARR;
    end = (PlWork *)&data_0212ceb0[4];
    if (plWork < end) {
        do {
            *((u8 *)&data_0212c594 + 4) = 0;
            plWork->unk_00 = 0;
            plWork->unk_01 = 0;
            plWork->unk_02 = 0;
            plWork->unk_03 = 0;
            plWork->unk_04 = 0;
            plWork->state = 0;
            plWork->unk_06 = 0;
            plWork->unk_07 = 0;
            plWork->unk_08 = 0;
            plWork->unk_0a = 0;
            plWork->unk_0b = 0;
            plWork->unk_0c = 0;
            plWork->unk_0d = 0;
            plWork->unk_0e = 0;
            plWork->unk_0f = 0;
            plWork->unk_10 = 0;
            plWork->unk_11 = 0;
            plWork->unk_12 = 0;
            plWork->unk_13 = 0;
            plWork->unk_14 = 0;
            plWork->unk_1b = 0;
            plWork->unk_1e = 0;
            plWork->unk_1f = 0;
            plWork->unk_20 = 0;
            plWork->unk_21 = 0;
            plWork->unk_22 = 0;
            plWork->unk_24 = 0;
            plWork->unk_34 = 0;
            plWork->unk_35 = 0;
            plWork->unk_36 = 0;
            plWork->unk_38 = 0;
            plWork->unk_39 = 0;
            plWork->unk_3a = 0;
            plWork->unk_3c = 0;
            plWork->unk_3d = 0;
            plWork->unk_26 = 0;
            plWork->yOffset = 0;
            plWork->unk_3e = (s32)plWork->unk_3e & ~0xc0;
            plWork->weapon = 0;
            plWork->unk_8b = (u8)(plWork->unk_8b & ~3) & ~0x70;
            OSi_CpuClear32(0xffffffff, plWork->unk_40, 0x40);
            plWork++;
        } while (plWork < end);
    }
    OSi_CpuClear32(0, plScratchBuffer, 0x140);
}
