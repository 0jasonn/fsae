#include "engine/functions.h"
#include "global.h"
#include "game/frame_load.h"

// parts_select(frame, flags) (0x0204d950): walks the part order table (data_021349e8) with the cursor in game state byte
// 0x4b until it finds a part of the current map level whose style bit (flags & 0x1f) is free and that is made for the
// current player count, and which passes the history checks (the wireless mode skips the single-error test).
PartRecord *parts_select(FRAME_INFO_ *frame, u32 flags) {
    u8 mapLevel;
    u32 styleBit;
    u8 mode;
    u8 cursor;
    PartEntry *entry;
    u32 entryFlags;
    PartRecord *part;

    mapLevel = get_maplevel();
    if (gameState.unk_8c != 0 && gameState.unk_8f == 0) {
        mode = gameState.unk_8d;
        styleBit = flags & 0x1f;
        while (TRUE) {
            if (data_021349e8[gameState.unk_49[2]] >= data_02103d48[gameState.unk_01]) {
                do {
                    gameState.unk_49[2] = (gameState.unk_49[2] + 1) & 0x3f;
                } while (data_021349e8[gameState.unk_49[2]] >= data_02103d48[gameState.unk_01]);
            }
            entry = &data_02103d88[gameState.unk_01][data_021349e8[gameState.unk_49[2]]];
            entryFlags = entry->flags;
            if (mode != entryFlags >> 30) {
                continue;
            }
            if ((entryFlags & (1 << styleBit)) == 0) {
                part = entry->part;
                if (part->playerCount == gameState.playerCount) {
                    if (pasthistoryCheck(entry) != 0) {
                        return part;
                    }
                }
            }
        }
    }
    styleBit = flags & 0x1f;
    while (TRUE) {
        cursor = (gameState.unk_49[2] + 1) & 0x3f;
        gameState.unk_49[2] = cursor;
        if (data_021349e8[cursor] >= data_02103d48[gameState.unk_01]) {
            continue;
        }
        entry = &data_02103d88[gameState.unk_01][data_021349e8[cursor]];
        if (mapLevel != entry->flags >> 30) {
            continue;
        }
        gameState.unk_8d = mapLevel;
        if ((entry->flags & (1 << styleBit)) == 0) {
            part = entry->part;
            if (part->playerCount == gameState.playerCount) {
                if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
                    if (checkSingleErrorParts(gameState.unk_01, part->partId) != 0) {
                        if (historyCheck(entry) != 0) {
                            return part;
                        }
                    }
                } else {
                    if (historyCheck(entry) != 0) {
                        return part;
                    }
                }
            }
        }
    }
}
