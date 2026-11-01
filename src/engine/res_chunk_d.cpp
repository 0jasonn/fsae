#include "engine/functions.h"
#include "global.h"
#include "engine/res_chunk_d_api.h"

// ResChunk_OpenRACH (ResChunk_OpenRACH, provisional name): finds the RACH chunk, runs ResChunk_RelocOff14 on its body and
// stores the body in *out. Returns 1 when the chunk exists, otherwise stores 0 and returns 0.
extern "C" s32 ResChunk_OpenRACH(u8 *base, u8 **out);
s32 ResChunk_OpenRACH(u8 *base, u8 **out) {
    u8 *chunk;

    chunk = (u8 *)ResChunk_Find(base, 0x43484152);
    if (chunk == 0) {
        *out = 0;
        return 0;
    }
    ResChunk_RelocOff14(chunk + 8);
    *out = chunk + 8;
    return 1;
}

// ResChunk_RelocOff14 (ResChunk_RelocOff14, provisional name): adds the body address to the word at +0x14 of the body.
void ResChunk_RelocOff14(u8 *self) {
    *(u32 *)(self + 0x14) += (u32)self;
}

// ResChunk_OpenRACH2 (ResChunk_OpenRACH2, provisional name): as ResChunk_OpenRACH with ResChunk_RelocOff14b as the setup.
extern "C" s32 ResChunk_OpenRACH2(u8 *base, u8 **out);
s32 ResChunk_OpenRACH2(u8 *base, u8 **out) {
    u8 *chunk;

    chunk = (u8 *)ResChunk_Find(base, 0x43484152);
    if (chunk == 0) {
        *out = 0;
        return 0;
    }
    ResChunk_RelocOff14b(chunk + 8);
    *out = chunk + 8;
    return 1;
}

// ResChunk_RelocOff14b (ResChunk_RelocOff14b, provisional name): the same relocation as ResChunk_RelocOff14.
void ResChunk_RelocOff14b(u8 *self) {
    *(u32 *)(self + 0x14) += (u32)self;
}

// ResChunk_OpenTTLP (ResChunk_OpenTTLP, provisional name): as ResChunk_OpenRACH for the TTLP chunk, with ResChunk_RelocOff0c
// as the setup.
extern "C" s32 ResChunk_OpenTTLP(u8 *base, u8 **out);
s32 ResChunk_OpenTTLP(u8 *base, u8 **out) {
    u8 *chunk;

    chunk = (u8 *)ResChunk_Find(base, 0x504c5454);
    if (chunk == 0) {
        *out = 0;
        return 0;
    }
    ResChunk_RelocOff0c(chunk + 8);
    *out = chunk + 8;
    return 1;
}

// ResChunk_RelocOff0c (ResChunk_RelocOff0c, provisional name): adds the body address to the word at +0xc of the body.
void ResChunk_RelocOff0c(u8 *self) {
    *(u32 *)(self + 0xc) += (u32)self;
}

// ResChunk_GetNRCS (ResChunk_GetNRCS, provisional name): stores the body of the NRCS chunk in *out. Returns 1 when the chunk
// exists, otherwise stores 0 and returns 0.
extern "C" s32 ResChunk_GetNRCS(u8 *base, u8 **out);
s32 ResChunk_GetNRCS(u8 *base, u8 **out) {
    u8 *chunk;

    chunk = (u8 *)ResChunk_Find(base, 0x5343524e);
    if (chunk != 0) {
        *out = chunk + 8;
        return 1;
    }
    *out = 0;
    return 0;
}

// ResChunk_Find (ResChunk_Find, provisional name): walks the chunks of base (the first chunk at +0xc, the count at +0xe, each
// chunk starts with its magic word and its size at +4) and returns the chunk with the magic, or 0.
void *ResChunk_Find(u8 *base, u32 magic) {
    u16 count;
    u16 i;
    u8 *cur;

    cur = base + *(u16 *)(base + 0xc);
    count = *(u16 *)(base + 0xe);
    for (i = 0; i < count; i++) {
        if (*(u32 *)cur == magic) {
            return cur;
        }
        cur += *(u32 *)(cur + 4);
    }
    return 0;
}
