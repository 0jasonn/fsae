#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"
#include "game/savemedia.h"

// Scroll and map unit 5 (module scr). Address -> name (original names):
//   0x020572b4 MultiRoomSet

extern "C" {
void MakeMapScreen(const void *src, void *dst);
}
extern u8 data_02158fa4[];
extern u8 data_0215bfa4[];
extern u8 data_02163fa8[];
extern u8 data_02166fa8[];
extern u8 data_02140fa0[];
extern u8 data_02158fa0[];
extern u8 data_02148fa0[];
extern u8 data_02163fa4[];
extern u8 data_02135640[];
extern u8 data_02135840[];
extern u32 em2f_mapFlag;

ARM void MultiRoomSet(void) {
    MIi_CpuCopy32(data_02158fa4, data_0215bfa4, 0x2000);
    MIi_CpuCopy32(data_02163fa8, data_02166fa8, 0x2000);
    MakeMapScreen(data_02140fa0, data_02158fa0);
    MakeMapScreen(data_02148fa0, data_02163fa4);
    MIi_CpuCopyFast(data_02135640, data_02135840, 0x20);
    em2f_mapFlag |= 0x200000;
}
