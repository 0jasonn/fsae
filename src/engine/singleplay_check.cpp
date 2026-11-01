#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/player.h"
#include "engine/objwork.h"

// Knife::Single::SinglePlay hit checks, 0x02094b64 to 0x02094d08: CheckBane (the OBJ_WORK_* overload and the helper
// overload), CheckTsubuAtari (two overloads) and CheckShell. The Thumb helper func_02083c8c (functions.h) takes an x, a y
// and a layer and returns a value that the checks compare.

extern "C" BOOL Knife_Single_SinglePlay_CheckBane_094b94(void *self, s16 x, s16 y, u16 layer);
extern "C" BOOL Knife_Single_SinglePlay_CheckTsubuAtari_094c0c(void *self, u8 kind, u32 mask, s16 x, s16 y, u16 layer);

// SinglePlay::CheckBane(OBJ_WORK_*, short, short) (0x02094b64): checks at the entity's position plus the offset
extern "C" BOOL Knife_Single_SinglePlay_CheckBane_094b64(void *self, Entity *e, s16 x, s16 y);
BOOL Knife_Single_SinglePlay_CheckBane_094b64(void *self, Entity *e, s16 x, s16 y) {
    return Knife_Single_SinglePlay_CheckBane_094b94(self, (s16)(e->x.HALF.HI + x), (s16)(e->y.HALF.HI + y), e->layer);
}

// SinglePlay::CheckBane(short, short, unsigned short) (0x02094b94): TRUE when the helper value is 0x16 to 0x1f
extern "C" BOOL Knife_Single_SinglePlay_CheckBane_094b94(void *self, s16 x, s16 y, u16 layer);
BOOL Knife_Single_SinglePlay_CheckBane_094b94(void *self, s16 x, s16 y, u16 layer) {
    u32 value;

    value = (u32)func_02083c8c(x, y, layer);
    if (value >= 0x16) {
        if (value <= 0x1f) {
            return TRUE;
        }
    }
    return FALSE;
}

// SinglePlay::CheckTsubuAtari(unsigned char, unsigned long, OBJ_WORK_*, short, short) (0x02094bc4)
extern "C" BOOL Knife_Single_SinglePlay_CheckTsubuAtari_094bc4(void *self, u8 kind, u32 mask, Entity *e, s16 x, s16 y);
BOOL Knife_Single_SinglePlay_CheckTsubuAtari_094bc4(void *self, u8 kind, u32 mask, Entity *e, s16 x, s16 y) {
    return Knife_Single_SinglePlay_CheckTsubuAtari_094c0c(self, kind, mask, (s16)(x + e->x.HALF.HI),
                                                           (s16)(y + e->y.HALF.HI), e->layer);
}

// SinglePlay::CheckTsubuAtari(unsigned char, unsigned long, short, short, unsigned short) (0x02094c0c): the 2x2 cell
// bit of the position, expanded by the mask, tested against the kind (0x1e and 0x1f map to 10 and 5)
BOOL Knife_Single_SinglePlay_CheckTsubuAtari_094c0c(void *self, u8 kind, u32 mask, s16 x, s16 y, u16 layer) {
    s16 xCell;
    s16 yCell;
    u8 cells;
    u8 spread;

    xCell = ((x >> 3) & 1) ^ 1;
    yCell = ((y >> 3) & 1) ^ 1;
    cells = (u8)((1 << xCell) << (yCell * 2));
    if (kind == 0x1e) {
        kind = 10;
    } else if (kind == 0x1f) {
        kind = 5;
    }
    if (mask < 2) {
        spread = (u8)(cells | ((cells & 0xa) >> 1) | ((cells & 5) << 1));
    } else {
        spread = (u8)(cells | ((cells & 0xc) >> 2) | ((cells & 3) << 2));
    }
    if (kind <= 0xe && (kind & spread) != 0) {
        return TRUE;
    }
    return FALSE;
}

// SinglePlay::CheckShell(OBJ_WORK_*, unsigned char) (0x02094ca0): the first entity of the list (SearchWork and
// SearchWorkNext, list 2) whose type byte differs from the entity's, or NULL
extern "C" Entity *Knife_Single_SinglePlay_CheckShell(void *self, Entity *e, u8 kind);
Entity *Knife_Single_SinglePlay_CheckShell(void *self, Entity *e, u8 kind) {
    Entity *found;

    found = SearchWork(kind, 2);
    if (found != NULL) {
        if (found->type == e->type) {
            return found;
        }
        found = SearchWorkNext(found, 2);
        if (found != NULL) {
            do {
                if (found->type == e->type) {
                    return found;
                }
                found = SearchWorkNext(found, 2);
            } while (found != NULL);
        }
    }
    return NULL;
}
