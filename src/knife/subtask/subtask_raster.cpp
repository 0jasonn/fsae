#include "engine/functions.h"
#include "knife/subtask/subtask_raster.h"
#include "knife/subtask/subtask_hblank.h"

#define SUBTASK_REG_IME (*(volatile u16 *)0x04000208)

// subtask_make_lobby_raster (0x0209a8b8): fills the per-scanline offsets 0x1f to 0x9f with the negated offset of each of
// the four 32 line groups
void subtask_make_lobby_raster(void) {
    SubtaskRasterWork **work;
    s32 line0, line1, line2, line3;
    s32 *offset0 = &data_0217d178;
    work = &data_0217d348;
    for (line0 = 0x1f; line0 < 0x3f; line0++) (*work)->rasterOffset[line0] = -*offset0;
    s32 *offset1 = &data_0217d17c;
    for (line1 = 0x3f; line1 < 0x5f; line1++) (*work)->rasterOffset[line1] = -*offset1;
    s32 *offset2 = &data_0217d180;
    for (line2 = 0x5f; line2 < 0x7f; line2++) (*work)->rasterOffset[line2] = -*offset2;
    s32 *offset3 = &data_0217d184;
    for (line3 = 0x7f; line3 < 0x9f; line3++) (*work)->rasterOffset[line3] = -*offset3;
}

// subtask_init_hblank_raster (0x0209a974): mode 1 builds the lobby raster and enables the HBlank interrupt, mode 0
// fills every line with the first offset and disables it again
void subtask_init_hblank_raster(s32 mode) {
    s32 line;
    u16 savedIme;

    if (mode != 0) {
        subtask_make_lobby_raster();
        GX_HBlankIntr(1);
        savedIme = SUBTASK_REG_IME;
        SUBTASK_REG_IME = 0;
        OS_SetIrqFunction(2, subtask_hblank_irq);
        OS_EnableIrqMask(2);
        savedIme = SUBTASK_REG_IME;
        SUBTASK_REG_IME = 1;
    } else {
        s32 *group = &data_0217d178;
        SubtaskRasterWork **work = &data_0217d348;
        for (line = 0; line < 0x100; line++) {
            (*work)->rasterOffset[line] = *group;
        }
        GX_HBlankIntr(0);
        savedIme = SUBTASK_REG_IME;
        SUBTASK_REG_IME = 0;
        OS_DisableIrqMask(2);
        savedIme = SUBTASK_REG_IME;
        SUBTASK_REG_IME = 1;
    }
}
