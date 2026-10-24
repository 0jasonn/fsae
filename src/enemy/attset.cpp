#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names attset, attreset):
//   attset, attreset

// Overlay of the actor field used by attset and attreset (offsets are those of Entity).
typedef struct Vars_Attset {
    /* 00 */ u8 unk_00[0x7a];
    /* 7a */ u8 savedAttr;   // attribute byte of the cell before attset overwrote it
} Vars_Attset;
#define VAtt(e) VARS(Vars_Attset, e)

typedef struct GridOrigin {
    u8 unk_00[0x18];
    u16 originX;
    u16 originY;
} GridOrigin;
extern GridOrigin data_0212c648;

// Attset: saves the attribute byte of the cell under the entity in the layer and marks it with 0x0f.
ARM void attset(Entity *e) {
    int bg = GetBgBuffAdrs(e->layer);
    u16 cell = (u16)(((e->x.HALF.HI - data_0212c648.originX) >> 4) | (((e->y.HALF.HI - data_0212c648.originY) >> 4) << 6));
    u8 *map = (u8 *)(bg + 4 + 0x2000);
    VAtt(e)->savedAttr = map[cell];
    map[cell] = 0xf;
}

// Attreset: writes the saved attribute byte back into the cell under the entity.
ARM void attreset(Entity *e) {
    int bg = GetBgBuffAdrs(e->layer);
    u16 cell = (u16)(((e->x.HALF.HI - data_0212c648.originX) >> 4) | (((e->y.HALF.HI - data_0212c648.originY) >> 4) << 6));
    u8 *map = (u8 *)(bg + cell + 0x2000);
    map[4] = VAtt(e)->savedAttr;
}
