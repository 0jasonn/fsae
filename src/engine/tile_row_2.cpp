#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/tile_record.h"

// tile_row_2: function TileMap_setupFromSrc (0x020b7528), matching. It follows TileBuffer_getRow. The kind byte of the
// source record selects TileMap_initWithOffset (kind 4) or func_020b7578 (kind 7, parked, the other tile map setup).

extern "C" void TileMap_initWithOffset(TileMap *self, void **src);
extern "C" void func_020b7578(void *self, void **src);

// TileMap_setupFromSrc(self, src) (0x020b7528, provisional name): sets up self from the record that src points to
// through its pointer. Returns self.
extern "C" void *TileMap_setupFromSrc(void *self, void **src);
ARM void *TileMap_setupFromSrc(void *self, void **src) {
    TileRecord *rec;

    rec = *(TileRecord **)*src;
    if (rec->kind != 4) {
        if (rec->kind == 7 && self != NULL) {
            func_020b7578(self, src);
        }
    } else {
        if (self != NULL) {
            TileMap_initWithOffset((TileMap *)self, src);
        }
    }
    return self;
}
