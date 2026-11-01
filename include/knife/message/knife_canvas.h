#ifndef WIP_E_KNIFE_CANVAS_H
#define WIP_E_KNIFE_CANVAS_H

#include "types.h"

// NitroSDK character canvas (NNSG2dCharCanvas): a buffer of 8x8 character cells.
typedef struct NNSG2dCharCanvas {
    void *pBits;   // 0x00: character data
    u32 width;     // 0x04: width in cells
    u32 height;    // 0x08: height in cells
    u8 colorDepth; // 0x0c: bits per pixel, 4 or 8
} NNSG2dCharCanvas;

// NitroSDK bit reader (NNSiG2dBitReader): reads bits from a byte stream, most significant bit first.
typedef struct NNSiG2dBitReader {
    u8 *ptr;       // 0x00: next byte to load
    s8 bitsLeft;   // 0x04: unread bits in bitBuf
    u8 bitBuf;     // 0x05: last byte loaded
} NNSiG2dBitReader;

s32 Knife_CharBytes(const NNSG2dCharCanvas *canvas);
u32 SpreadColor32(const NNSG2dCharCanvas *canvas, int color);
void Knife_ClearContinuous(const NNSG2dCharCanvas *canvas, s32 color);
u32 NNSi_G2dBitReaderRead(NNSiG2dBitReader *reader, s32 bits);

#endif
