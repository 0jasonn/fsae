#include "engine/functions.h"
// Functions in this file:
//   BgmSet -> BgmSet
//   GameState_SetTrackVariant -> GameState_SetTrackVariant
#include "game/gamestateview_c.h"
#include "global.h"

typedef struct MusicIndexEntry {
    /* 00 */ const u8 *table;
    /* 04 */ u32 unk_04;
} MusicIndexEntry;

extern const u32 bgmGameModeTracks[];
extern const u32 bgmSpecialTracks[];
extern const MusicIndexEntry *const bgmIndexTable[];
extern const u32 bgmVariantTracks[];


ARM void BgmSet(void) {
    u32 trackId;
    u16 current;
    if (data_0212c7c8.unk_6e >= 2) {
        return;
    }
    if (data_0212c7c8.periodicFlag != 0) {
        return;
    }
    current = data_0212c7c8.unk_26;
    if (current == 0x1a1) {
        return;
    }
    if (data_0212c7c8.pickIndex >= 5) {
        if (data_0212c7c8.pickIndex == 5) {
            trackId = bgmSpecialTracks[data_0212c7c8.unk_48];
        } else {
            trackId = bgmVariantTracks[bgmIndexTable[data_0212c7c8.gameMode][data_0212c7c8.unk_48].table[1]];
        }
    } else {
        trackId = bgmGameModeTracks[data_0212c7c8.gameMode];
    }
    if (data_0212c7c8.unk_24 != 0) {
        trackId = 0x1a9;
    }
    if (data_0212c7c8.unk_50[1] != 0) {
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
    data_0212c7c8.unk_26 = (u16)trackId;
    SoundReq(trackId);
}

ARM void GameState_SetTrackVariant(void) {
    u8 key;
    data_0212c7c8.unk_8e = 0;
    if (data_0212c7c8.pickIndex < 5) {
        return;
    }
    key = bgmIndexTable[data_0212c7c8.pickIndex][data_0212c7c8.unk_48].table[1];
    switch (key) {
        case 7:
            data_0212c7c8.unk_8e = 1;
            break;
        case 8:
            data_0212c7c8.unk_8e = 2;
            break;
        case 6:
            data_0212c7c8.unk_8e = 3;
            break;
        case 9:
            data_0212c7c8.unk_8e = 4;
            break;
        case 10:
            data_0212c7c8.unk_8e = 5;
            break;
        case 11:
            data_0212c7c8.unk_8e = 6;
            break;
        case 12:
            data_0212c7c8.unk_8e = 7;
            break;
        case 13:
            data_0212c7c8.unk_8e = 8;
            break;
        case 14:
            data_0212c7c8.unk_8e = 9;
            break;
        default:
            break;
    }
}
