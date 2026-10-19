#include "engine/functions.h"
#include "enemy/enemycommon.h"
#include "global.h"

// Implementer B, round 6: MultiEventSet (0x0204602c), ParseTypeBits (0x020460e8).
// ParseTypeBits copies data_020d42b4 (8 words) to the stack.

// MultiEventSet (0x0204602c): walks a list of 8-byte event records until the 0xffff terminator. Each record is
// registered as a stop block; the matching actors get their area and item bookkeeping updated.
ARM void MultiEventSet(u16 *list, u8 a, u8 b, u8 c) {
    Entity *e;
    if (list[0] == 0xffff) {
        return;
    }
    do {
        if (RegistStopBlock(list, c) != 0) {
            e = GetObjWork();
            if (e != NULL) {
                if (func_02085024(e, list, c) != 0) {
                    e->areaIndex = c;
                    if (e->objKind == 6) {
                        if (e->objId != 0x21) {
                            if (e->objId == 0x2d) {
                                data_021348f8[e->timer & 3] = e->type2;
                            }
                        } else {
                            e->unk_20 = ItemRegist(e->type);
                            data_021348f8[e->timer & 3] = e->type;
                        }
                    }
                }
            }
        }
        list += 4;
    } while (list[0] != 0xffff);
}

// ParseTypeBits (0x020460e8): the bit for a type code, taken from the table in data_020d42b4.
ARM u32 ParseTypeBits(u8 type) {
    ParseTypeTable table = data_020d42b4;
    return table.bits[(type & 0xe0) >> 5] << (type & 0x1f);
}
