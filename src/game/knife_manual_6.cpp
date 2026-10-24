#include "engine/functions.h"
#include "global.h"
#include "game/g_knife_manual.h"
#include "game/decls_g.h"

// Functions in this file (original names from the debug build):
//   Knife::i_initM2dLibrary (0x020c7da0)

// 21-byte configuration block copied from rodata (data_020df1e8) into a local of i_initM2dLibrary
typedef struct KnifeM2dConfig {
    u8 bytes[21];
} KnifeM2dConfig;

extern const KnifeM2dConfig data_020df1e8;

namespace Knife {

// Knife::i_initM2dLibrary() (0x020c7da0): copies the configuration block, builds three slot pointers into
// data_02187070 (8 bytes apart) and passes them with the manual object to the library setup
ARM void i_initM2dLibrary(void) {
    void *slots[3];
    KnifeM2dConfig config;
    s32 i;

    config = data_020df1e8;
    for (i = 0; i < 3; i++) {
        slots[i] = (u8 *)data_02187070 + i * 8;
    }
    func_020befd0(&data_0218704c, data_02187050, &config, data_021271ac, slots);
}

}
