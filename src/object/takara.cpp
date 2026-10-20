#include "engine/functions.h"
#include "game/stageseldecls.h"

// Treasure chest module. Address -> name (dsd names without an original name):
//   0x0207bcd4 takara_resetFlags

// takara_resetFlags, 0x0207bcd4. Clears the opened-chest flags and the 0x80-byte chest table.
ARM void takara_resetFlags(void) {
    data_0213491c = 0;
    OSi_CpuClear32(0xffffffff, data_02134c30, 0x80);
}

// TakaraOpen, 0x0207bd00. Opens the chest with this id: the first time, plays the sound, sets its flag, runs the
// handler of its table entry and, if the cell reports the expected state, rewrites the cell.
ARM void TakaraOpen(Entity *e, u16 id, u16 key) {
    u8 index = 0;
    TakaraEntry *entry = data_02134c30;
    do {
        if (entry->id == id) {
            break;
        }
        index = index + 1;
        entry++;
    } while (index < 0x20);
    if (entry == &data_02134c30[0x20]) {
        return;
    }
    if ((data_0213491c & flagBits[index]) != 0) {
        return;
    }
    SoundReq(0x21);
    data_0213491c = data_0213491c | flagBits[index];
    func_02083ca8(id, key);
    data_02116800[entry->unk_02 & 0x1f](entry, e, id);
    if (func_02083ca8(id, key) != 0x107) {
        return;
    }
    RewCell(0x108, id, key);
}
