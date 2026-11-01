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


#include "engine/player.h"

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



void PlWorkReset(void) {
    PlayerData *end;
    PlayerData *player;

    player = data_0212ceb0;
    end = &data_0212ceb0[4];
    if (player < end) {
        do {
            *((u8 *)&data_0212c594 + 4) = 0;
            player->unk_00 = 0;
            player->unk_01 = 0;
            player->unk_02 = 0;
            player->unk_03 = 0;
            player->inUse = 0;
            player->specialState = 0;
            player->unk_06 = 0;
            player->unk_07 = 0;
            player->motionId = 0;
            player->unk_0a = 0;
            player->unk_0b = 0;
            player->state = 0;
            player->unk_0d = 0;
            player->unk_0e = 0;
            player->unk_0f = 0;
            player->unk_10 = 0;
            player->unk_11 = 0;
            player->unk_12 = 0;
            player->unk_13 = 0;
            player->unk_14 = 0;
            player->actionFlags = 0;
            player->hitFlags = 0;
            player->unk_1f = 0;
            player->unk_20 = 0;
            player->tameState = 0;
            player->unk_22 = 0;
            player->unk_24 = 0;
            player->unk_34 = 0;
            player->unk_35 = 0;
            player->statusFlags = 0;
            player->stateTimer = 0;
            player->unk_39 = 0;
            player->unk_3a = 0;
            player->callState = 0;
            player->unk_3d = 0;
            player->unk_26 = 0;
            player->yOffset = 0;
            player->unk_3e = (s32)player->unk_3e & ~0xc0;
            player->weapon = 0;
            player->paletteBits = (u8)(player->paletteBits & ~3) & ~0x70;
            OSi_CpuClear32(0xffffffff, player->unk_40, 0x40);
            player++;
        } while (player < end);
    }
    OSi_CpuClear32(0, plScratchBuffer, 0x140);
}
