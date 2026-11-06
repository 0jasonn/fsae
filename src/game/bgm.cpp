#include "engine/functions.h"
// Functions in this file:
//   BgmSet -> BgmSet
//   GameState_SetTrackVariant -> GameState_SetTrackVariant
#include "game/player_flags.h"
#include "global.h"

typedef struct MusicIndexEntry {
    /* 00 */ const u8 *table;
    /* 04 */ u32 unk_04;
} MusicIndexEntry;

extern const u32 bgmGameModeTracks[];
extern const u32 bgmSpecialTracks[];
extern const MusicIndexEntry *const bgmIndexTable[];
extern const u32 bgmVariantTracks[];


void BgmSet(void) {
    u32 trackId;
    u16 current;
    if (gameState.unk_6e >= 2) {
        return;
    }
    if (gameState.periodicFlag != 0) {
        return;
    }
    current = gameState.unk_26;
    if (current == 0x1a1) {
        return;
    }
    if (gameState.unk_01 >= 5) {
        if (gameState.unk_01 == 5) {
            trackId = bgmSpecialTracks[gameState.unk_48];
        } else {
            trackId = bgmVariantTracks[bgmIndexTable[gameState.gameMode][gameState.unk_48].table[1]];
        }
    } else {
        trackId = bgmGameModeTracks[gameState.gameMode];
    }
    if (gameState.unk_24 != 0) {
        trackId = 0x1a9;
    }
    if (gameState.unk_50[1] != 0) {
        trackId = 0x1aa;
    }
    if (current == (u16)trackId) {
        return;
    }
    if (current != 0xffff) {
        SoundReq(0x80080000);
    } else {
        trackId = (u16)trackId;
    }
    gameState.unk_26 = (u16)trackId;
    SoundReq(trackId);
}

void GameState_SetTrackVariant(void) {
    u8 key;
    gameState.unk_8e = 0;
    if (gameState.unk_01 < 5) {
        return;
    }
    key = bgmIndexTable[gameState.unk_01][gameState.unk_48].table[1];
    switch (key) {
        case 7:
            gameState.unk_8e = 1;
            break;
        case 8:
            gameState.unk_8e = 2;
            break;
        case 6:
            gameState.unk_8e = 3;
            break;
        case 9:
            gameState.unk_8e = 4;
            break;
        case 10:
            gameState.unk_8e = 5;
            break;
        case 11:
            gameState.unk_8e = 6;
            break;
        case 12:
            gameState.unk_8e = 7;
            break;
        case 13:
            gameState.unk_8e = 8;
            break;
        case 14:
            gameState.unk_8e = 9;
            break;
        default:
            break;
    }
}
