#include "engine/functions.h"
#include "engine/objaffine.h"

// Affine parameter block of one OBJ affine entry (0x20 bytes): pa, pb, pc, pd sit at 0x06, 0x0e, 0x16, 0x1e
typedef struct ObjAffineParams {
    /* 00 */ u8 unk_00[6];
    /* 06 */ u16 pa;
    /* 08 */ u8 unk_08[6];
    /* 0e */ u16 pb;
    /* 10 */ u8 unk_10[6];
    /* 16 */ u16 pc;
    /* 18 */ u8 unk_18[6];
    /* 1e */ u16 pd;
} ObjAffineParams;

// Input of func_02083000: a scale x, a scale y and an angle (u16, 0x10000 is a full turn)
typedef struct AffineScaleArgs {
    /* 00 */ s16 scaleX;
    /* 02 */ s16 scaleY;
    /* 04 */ u16 angle;
} AffineScaleArgs;

// func_02083000 (0x02083000): builds the 2x2 matrix of a rotation by angle with the scale applied and stores its entries
// (>> 4) into the affine parameters of dst
void func_02083000(const void *src, void *dst) {
    const AffineScaleArgs *args = (const AffineScaleArgs *)src;
    ObjAffineParams *params = (ObjAffineParams *)dst;
    s32 mtx[4];
    s32 scaleX;
    s32 scaleY;
    int index;

    index = args->angle >> 4;
    scaleX = args->scaleX << 4;
    scaleY = args->scaleY << 4;
    func_02012ad0(mtx, data_020c91fc[index * 2], data_020c91fc[index * 2 + 1]);
    MTX_ScaleApply22(mtx, mtx, scaleX, scaleY);
    params->pa = mtx[0] >> 4;
    params->pb = mtx[1] >> 4;
    params->pc = mtx[2] >> 4;
    params->pd = mtx[3] >> 4;
}
