#include "engine/functions.h"
#include "engine/em12_type_masks.h"
#include "game/stopblock_4.h"
#include "actor/enemy/rewcell_one.h"

// StopBlockManager() (0x0204e958): per-frame pass over the two stop block tables. A block whose first condition
// (type bits in em12_typeMasks) is met removes its cell and puffs smoke; the second condition restores the cell below
// it. Finished blocks are cleared and each table is compacted when something changed. The second table also spawns the
// actors of its entries when their condition is met.
void StopBlockManager(void) {
    STOPBLOCK_WORK_ *block;
    u32 bits;
    u8 changed = 0;
    u16 kind;

    for (block = data_02134f30; block < data_02134f30 + 0x30; block++) {
        if (block->key == 0) {
            break;
        }
        if (!(block->key & 0x2000)) {
            bits = ParseTypeBits(block->state);
            if (block->state == 0xff || bits == (bits & em12_typeMasks[(block->key & 0x1000) >> 12])) {
                block->state = 0xff;
                RewCellOne(0x136, block->key & 0xfff, block->key & 0xc000);
                sbKemuriSet(block);
                block->key |= 0x2000;
            }
        }
        if (block->unk_03 != 0xff) {
            bits = ParseTypeBits(block->unk_03);
            if (bits == (bits & em12_typeMasks[(block->key & 0x1000) >> 12])) {
                block->unk_03 = 0xff;
                RewCellBack(block->key & 0xfff, block->key & 0xc000);
                kind = GetCellKind(block->key & 0xfff, block->key & 0xc000);
                if (kind >= 0x176 && kind <= 0x179) {
                    set5c_changeiroankyo(block->key & 0xfff, kind);
                }
                sbKemuriSet(block);
            }
            changed = 1;
            if (block->state == 0xff && block->unk_03 == 0xff) {
                block->key = 0;
            }
        }
    }
    if (changed != 0) {
        sbGarbageCollection(data_02134f30, data_02134f30 + 0x30);
    }
    changed = 0;
    for (block = data_02134ff0; block < data_02134ff0 + 0x30; block++) {
        if (block->key == 0) {
            break;
        }
        bits = ParseTypeBits(block->state);
        if (bits == (bits & em12_typeMasks[(block->key & 0x1000) >> 12])) {
            Entity *spawned = GetSetWork(8, block->state, (u8)(block->unk_03 | 0x80));
            if (spawned != NULL) {
                spawned->x.HALF.HI = ((block->key & 0x3f) << 4) | 8;
                spawned->y.HALF.HI = ((block->key & 0xfc0) >> 2) | 8;
                spawned->areaIndex = (block->key & 0x1000) >> 12;
            }
            block->key = 0;
            changed = 1;
        }
    }
    if (changed != 0) {
        sbGarbageCollection(data_02134ff0, data_02134ff0 + 0x30);
    }
}
