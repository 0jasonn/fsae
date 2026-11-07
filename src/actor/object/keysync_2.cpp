#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/comm/comm.h"

// Key synchronisation of the wireless players (module keysync): keysync_init (0x0202877c), keysync_move (0x02028804).

extern u8 comWork[];
extern u8 data_0212c9ec[];
extern u32 data_0212c538;
extern u8 data_02134cb0[];

// keysync_init (0x0202877c): clears the key buffers and copies the cleared entry of the last two players over the
// other three history rows.
void keysync_init(void) {
    u8 i;
    u16 *keyHistory = (u16 *)data_02134cb0;

    MIi_CpuClear16(0xc000, data_02134cb0, 0x80);
    for (i = 0xe; i < 0x10; i++) {
        keyHistory[i + 0x30] = 0;
        keyHistory[i] = keyHistory[i + 0x10] = keyHistory[i + 0x20] = keyHistory[i + 0x30];
    }
    MIi_CpuClear16(0, data_0212c9ec, 0x34);
    data_0212c538 = 0;
    comWork[1] += 1;
}

// keysync_move (0x02028804): per-frame key synchronisation of the wireless players; calls key_update for every player the
// comm block flags and acknowledges the frame.
void keysync_move(void) {
    *(u32 *)(comWork + 8) = 3;
    comWork[0x44] = comWork[0x10] = 0x50;
    if (CommStatusSync(0x50) == 0) {
        return;
    }
    if (comWork[3] & 1) {
        key_update(0);
    }
    if (comWork[3] & 2) {
        key_update(1);
    }
    if (comWork[3] & 4) {
        key_update(2);
    }
    if (comWork[3] & 8) {
        key_update(3);
    }
    frame_ack();
}
