#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "engine/vgroup.h"

// VGroupManager (0x02080ed4), the VGroup module's per-frame loader.
// VGroupInit (0x02080e58) is in src/engine/vgroup.cpp.

extern "C" u16 GetResTranslateID(u16 id, const void *table, s32 count); // plain name, defined in src/game/resid.cpp
BOOL MdmaCheck(void);

// Takes the first queued request whose slot is ready (MdmaCheck), loads its graphics from the Zelda resource into VRAM,
// then either frees its slot or, when bit 31 of its header is set, requeues the rest of the request.
void VGroupManager(void) {
    u8 slot;
    s32 size;
    u16 id;
    u32 *request;
    void *graphics;

    for (slot = 8; slot < 0x2b; slot++) {
        if (vgroupQueue[slot] == 0) {
            continue;
        }
        if (!MdmaCheck()) {
            continue;
        }
        request = (u32 *)vgroupQueue[slot];
        id = (s16)(request[0] & 0xffffff);
        size = 0;
        if (gameState.unk_8e >= 6) {
            switch (id - 0xd9) {
            case 0:
            case 7:
            case 14:
            case 20:
                id = 0x114;
                break;
            case 1:
            case 8:
            case 15:
            case 21:
                id = 0x115;
                break;
            case 2:
            case 9:
            case 16:
            case 22:
                id = 0x116;
                break;
            }
        } else {
            id = GetResTranslateID(id, vgroupIdTable, 0x3b);
        }
        graphics = KnifeApp_getZeldaResource_08dde0(KnifeApp_getInstance(), &size, id);
        func_020845b0((slot << 9) + 0x6400000, graphics, (u16)size);
        vgroupQueue[slot] = 0;
        if (!(request[0] & 0x80000000)) {
            vgroupSlots[vgroupSlots[slot].state & 0x3f].state &= 0xbf;
        } else {
            vgroupQueue[(u8)(slot + (u8)((request[1] + 0x1ff) >> 9))] = (u32)((u8 *)request + 8);
        }
        return;
    }
}
