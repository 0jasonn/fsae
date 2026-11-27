#include "engine/functions.h"
#include "engine/player.h"
#include "game/frame_load.h"
#include "engine/floor_parts_state.h"

// Functions in this file (original names from the debug build): parts_init

// parts_init() (0x0204d650): at the start of a run builds the part order tables (identity, shuffled with a Fisher-Yates
// pass, or a transposed 3x3 layout in modes 5 and 6) and clears the part history. The transpose reuses the shuffle's
// counters (i outer, other inner): that gives the ROM's registers.
void parts_init(void) {
    u32 i;
    u32 swap;
    u32 other;

    if (gameState.phaseTimer != 0) {
        return;
    }
    i = 0;
    gameState.unk_49[2] = 0;
    gameState.unk_49[0] = 0;
    for (; i < 0x40; i++) {
        u8 value = i;
        data_021349e8[i] = value;
        data_02134a28[i] = value;
    }
    if (gameState.unk_01 != 5 && gameState.unk_01 != 6) {
        for (i = 0x3f; i != 0; i--) {
            other = Random() % i;
            swap = data_021349e8[i];
            data_021349e8[i] = data_021349e8[other];
            data_021349e8[other] = swap;
        }
        for (i = 0x3f; i != 0; i--) {
            other = Random() % i;
            swap = data_02134a28[i];
            data_02134a28[i] = data_02134a28[other];
            data_02134a28[other] = swap;
        }
    } else {
        for (i = 0; i < 3; i++) {
            for (other = 0; other < 3; other++) {
                data_02134a28[i * 3 + other] = i + other * 3;
            }
        }
    }
    OSi_CpuClear32(0, data_0216f834, 0x80);
    OSi_CpuClear32(0, data_0216f8b4, 0x80);
    data_0216f820.flags = 0;
}
