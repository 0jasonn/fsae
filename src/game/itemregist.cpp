#include "actor/enemy/enemycommon.h"
#include "global.h"

// ItemRegist (0x02046130): returns the OAM tile offset (0xc0 + 4 * slot) of an item graphic, uploading it into the next
// free 0x80-byte slot of the object VRAM the first time it is requested. Returns 0 when all eight slots are taken.
u8 ItemRegist(u8 type) {
    u8 count = data_021348e8;
    u8 i;
    if (count == 8) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        if (data_02134934[i] == type) {
            break;
        }
    }
    if (i != count) {
        return i * 4 + 0xc0;
    }
    func_020845b0(0x06405800 + data_021348e8 * 0x80, Cockpit_GetGfxAddr(type), 0x80);
    u8 *entry = data_02134934 + data_021348e8;
    u8 offset = data_021348e8 * 4 + 0xc0;
    data_021348e8++;
    *entry = type;
    return offset;
}
