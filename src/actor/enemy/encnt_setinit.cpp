#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/encnt.h"

void encnt_setinit(void) {
    u8 index;
    int retry;
    u8 i;
    u8 angle;
    EncntListHead *head;
    EncntNode *node;
    Entity *player;
    EncntEntry *entry;

    index = (Random() & 3) * 2;
    encntState.posA = encntState.table[index];
    encntState.posB = encntState.table[index + 1];
    encntState.limit = (encntState.table[index + 1] & 0x700) >> 8;
    encntState.kind = (encntState.table[index + 1] & 0xf000) >> 12;
    encntState.timerReload = (Random() & 1) + 3;
    retry = 0;
    for (head = data_0212c6b0; head < data_0212c6b0 + 8; head++) {
        for (node = head->next; node != (EncntNode *)head; node = node->next) {
            if (node->tag == 3 && node->subtag == encntState.posA) {
                if (retry++ > 8) {
                    nextset();
                    return;
                }
            }
        }
    }
    player = encntState.entity;
    angle = Random() & 0x1c;
    for (i = 0; i < encntState.limit; i++) {
        entry = &encntState.entries[i];
        entry->x = (u16)player->x.HALF.HI;
        entry->y = player->y.HALF.HI;
        entry->angle = angle;
        entry->taken = 0;
        entry->initialised = 0;
        angle = (angle + 4) & 0x1c;
    }
    encntState.count++;
    encntState.timer = encntState.timerReload;
}
