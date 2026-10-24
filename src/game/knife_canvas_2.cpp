#include "engine/functions.h"
#include "global.h"
#include "game/knife_canvas.h"

// Functions in this file (original names from the debug build):
//   Knife_ClearContinuous (0x0209ffb8); NNSi_G2dBitReaderRead (0x0209ffec) is parked in scratch/agentE/nonmatching

// Knife_ClearContinuous(NNSG2dCharCanvas const*, int) (0x0209ffb8): fills the whole canvas with one colour
ARM void Knife_ClearContinuous(const NNSG2dCharCanvas *canvas, int color) {
    u32 spread = SpreadColor32(canvas, color);

    MIi_CpuClearFast(spread, canvas->pBits, canvas->width * canvas->height * Knife_CharBytes(canvas));
}
