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



ARM void PlWorkReset(void) {
    PlWork *end;
    PlWork *p;

    p = PL_ARR;
    end = (PlWork *)&data_0212ceb0[4];
    if (p < end) {
        do {
            *((u8 *)&data_0212c594 + 4) = 0;
            p->unk_00 = 0;
            p->unk_01 = 0;
            p->unk_02 = 0;
            p->unk_03 = 0;
            p->unk_04 = 0;
            p->state = 0;
            p->unk_06 = 0;
            p->unk_07 = 0;
            p->unk_08 = 0;
            p->unk_0a = 0;
            p->unk_0b = 0;
            p->unk_0c = 0;
            p->unk_0d = 0;
            p->unk_0e = 0;
            p->unk_0f = 0;
            p->unk_10 = 0;
            p->unk_11 = 0;
            p->unk_12 = 0;
            p->unk_13 = 0;
            p->unk_14 = 0;
            p->unk_1b = 0;
            p->unk_1e = 0;
            p->unk_1f = 0;
            p->unk_20 = 0;
            p->unk_21 = 0;
            p->unk_22 = 0;
            p->unk_24 = 0;
            p->unk_34 = 0;
            p->unk_35 = 0;
            p->unk_36 = 0;
            p->unk_38 = 0;
            p->unk_39 = 0;
            p->unk_3a = 0;
            p->unk_3c = 0;
            p->unk_3d = 0;
            p->unk_26 = 0;
            p->yOffset = 0;
            p->unk_3e = (s32)p->unk_3e & ~0xc0;
            p->weapon = 0;
            p->unk_8b = (u8)(p->unk_8b & ~3) & ~0x70;
            OSi_CpuClear32(0xffffffff, p->unk_40, 0x40);
            p++;
        } while (p < end);
    }
    OSi_CpuClear32(0, data_0212c868, 0x140);
}
