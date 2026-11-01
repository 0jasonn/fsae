#include "engine/functions.h"
#include "global.h"
#include "engine/res_chunk_a_api.h"
#include "engine/res_chunk_d_api.h"

extern "C" u8 data_020df02c[];

// ObjRes_Init (ObjRes_Init, provisional name): stores the class table at +0 and the two words a and b at +4 and +8,
// and clears the word at +0xc.
void ObjRes_Init(u8 *self, u32 a, u32 b) {
    *(u8 **)self = data_020df02c;
    *(u32 *)(self + 4) = a;
    *(u32 *)(self + 8) = b;
    *(u32 *)(self + 0xc) = 0;
}

// ResChunk_OpenKNBA (ResChunk_OpenKNBA, provisional name): finds the KNBA chunk in base, runs func_020c2cc0 on its body and
// stores the body in *out. Returns 1 when the chunk exists, otherwise stores 0 and returns 0.
extern "C" s32 ResChunk_OpenKNBA(u8 *base, u8 **out);
s32 ResChunk_OpenKNBA(u8 *base, u8 **out) {
    u8 *chunk;

    chunk = (u8 *)ResChunk_Find(base, 0x41424e4b);
    if (chunk == 0) {
        *out = 0;
        return 0;
    }
    func_020c2cc0(chunk + 8);
    *out = chunk + 8;
    return 1;
}
