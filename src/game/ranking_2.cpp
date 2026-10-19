#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"

// Ranking screen unit 2 (module ranking, after src/game/ranking.cpp). Address -> name:
//   0x020552c0 ranking_write_rupee (original name, matches)

ARM void ranking_write_rupee(u16 *cells, u32 value, u8 digits, u16 palette) {
    while (digits != 0) {
        u16 digit = value % 10;
        cells[0] = (digit + 0x20) | palette;
        cells[0x20] = (digit + 0x40) | palette;
        value /= 10;
        digits--;
        cells--;
    }
}
