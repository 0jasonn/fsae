#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/comm/singleplay_warp_api.h"

// Knife::Single::SinglePlay::WarpAtariCheck (0x020954f0): calls the Thumb helper func_0208a06c on the entity, then
// reports whether the four three-bit groups of the entity's wall flags at 0x2c (bits 13-15, 9-11, 5-7 and 1-3) are all set.
// The flags are written back unchanged.

BOOL Knife_Single_SinglePlay_WarpAtariCheck(void *self, Entity *e) {
    u16 saved;
    u16 flags;
    BOOL group1;
    BOOL group2;
    BOOL group3;

    saved = e->wallFlags;
    func_0208a06c(e);
    group3 = group2 = group1 = FALSE;
    flags = e->wallFlags;
    if (flags & 0xe000) {
        if (flags & 0xe00) {
            group3 = TRUE;
        }
    }
    if (group3) {
        if (flags & 0xe0) {
            group2 = TRUE;
        }
    }
    if (group2) {
        if (flags & 0xe) {
            group1 = TRUE;
        }
    }
    e->wallFlags = saved;
    return group1;
}
