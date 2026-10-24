#include "engine/functions.h"
#include "global.h"
#include "game/knife_canvas.h"

// Functions in this file (original names from the debug build):
//   Knife_CharBytes is named Knife_CharBytes here (bytes of one cell); SpreadColor32 (0x0209fcdc) is parked in scratch/agentE/nonmatching

// Bytes of one 8x8 cell at the canvas colour depth: 64 pixels at 8 bits, 32 at 4 bits
ARM s32 Knife_CharBytes(const NNSG2dCharCanvas *canvas) {
    return canvas->colorDepth * 64 / 8;
}
