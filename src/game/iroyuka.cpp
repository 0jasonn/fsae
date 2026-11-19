#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/player.h"
#include "engine/misc.h"
#include "game/map.h"
#include "game/iroyuka_2.h"
#include "engine/floor_parts_state.h"

// Functions in this file (original names from the debug build):
//   ChangeIroyuka


// Sets the pending iroyuka index (value + 1) when the game state is not 1 and there are cell entries
void ChangeIroyuka(u8 value) {
    if (gameState.unk_01 != 1 && data_0216f820.iroyukaCount != 0) {
        data_0216f820.iroyukaIndex = value + 1;
    }
}

// Functions in this file (original names from the debug build):
//   UpdateIroyuka (0x0204d3ac)

// One entry of the cell table: the cell to match and the cell flags passed to RewCellOne
typedef struct IroyukaCellEntry {
    u16 cell;
    u16 flags;
} IroyukaCellEntry;
extern IroyukaCellEntry data_0216f934[];

// UpdateIroyuka() (0x0204d3ac): when a pending index is set and no blend is running, walks the table and
// rewrites the cells it lists, then copies the two halves of the palette block of the selected player to VRAM
void UpdateIroyuka(void) {
    u8 *resource;
    u8 index;
    u32 i;
    int ret;
    u32 paletteIdx;
    PlayerData *player;

    if (data_0216f820.iroyukaIndex == 0) {
        return;
    }
    if (blendRequest.blendEnabled != 0) {
        return;
    }
    resource = KnifeApp_getZeldaResource_08ddcc(KnifeApp_getInstance(), 0xa4);
    index = (u8)(data_0216f820.iroyukaIndex - 1);
    for (i = 0; i < data_0216f820.iroyukaCount; i++) {
        if (index != data_0216f934[i].cell - 0xf) {
            ret = func_02083d00(data_0216f934[i].flags - 0x40, 0x4000);
            if (ret == 0x43 || ret == 6) {
                RewCellOne(0x13, data_0216f934[i].flags, 0x4000);
            } else {
                RewCellOne(0x14, data_0216f934[i].flags, 0x4000);
            }
        } else {
            RewCellOne(data_0216f934[i].cell, data_0216f934[i].flags, 0x4000);
        }
    }
    player = &playerWork[index];
    paletteIdx = ((u32)player->paletteBits << 28) >> 30;
    SetDataVBlank(resource + (paletteIdx << 7), (void *)0x0600cc00, 0x40);
    paletteIdx = ((u32)player->paletteBits << 28) >> 30;
    SetDataVBlank(resource + (paletteIdx << 7) + 0x40, (void *)0x0600d000, 0x40);
    data_0216f820.iroyukaIndex = 0;
}
