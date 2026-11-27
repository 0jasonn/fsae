#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/encnt.h"

// Spawn trigger record of the area info table (GetInfoAdrs kind 4), 8 bytes; the list ends with x == 0xff.
typedef struct AreaTrigger {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u8 spawnId[4];
} AreaTrigger;

// area_check (0x020438b4): true when the encounter player stands inside one of the trigger rectangles of the area's info
// table (kind 4) and that trigger has a spawn table for the current mode/level; it then selects the table.
BOOL area_check(u8 area) {
    AreaTrigger *trigger;
    Entity *player;
    u16 x;    // trigger x, then the player's x offset inside it
    u16 y;    // trigger y, then the player's y offset inside it
    u16 w;
    u16 h;
    u8 id;

    player = encntState.entity;
    trigger = (AreaTrigger *)GetInfoAdrs(area, 4);
    if (trigger == NULL) {
        return 0;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0 && (playerKeysPrev[player->type] & 0x1000)) {
        return 0;
    }
    for (; trigger->x != 0xff; trigger++) {
        x = data_0213492c[area].x + trigger->x * 16;
        y = data_0213492c[area].y + trigger->y * 16;
        x = player->x.HALF.HI - (s16)x;
        y = player->y.HALF.HI - (s16)y;
        w = trigger->width << 4;
        h = trigger->height << 4;
        if (x < w && y < h) {
            id = trigger->spawnId[gameState.unk_01 == 2 ? gameState.difficulty : gameState.level - 1];
            if (id != 0) {
                encntState.table = (const u16 *)(data_020f279c + id * 16);
                return 1;
            }
        }
    }
    return 0;
}
