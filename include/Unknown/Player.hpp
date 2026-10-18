#ifndef UNKNOWN_PLAYER_HPP
#define UNKNOWN_PLAYER_HPP

#include "Unknown/Entity.hpp"

// Per-player state, one per connected Link
struct PlayerData {
    /* 00 */ u8 unk_00[0xc];
    /* 0c */ u8 unk_0c;
    /* 0d */ u8 unk_0d[0x11];
    /* 1e */ u8 unk_1e;
    /* 1f */ u8 unk_1f[7];
    /* 26 */ u8 unk_26;
    /* 27 */ u8 unk_27;
    /* 28 */ Entity *unk_28;
    /* 2c */ u8 unk_2c[0xa];
    /* 36 */ u16 unk_36;
    /* 38 */ u8 unk_38;
    /* 39 */ u8 unk_39[0x5b];
}; // size 0x94

extern PlayerData data_0212ceb0[4];
struct UnkStruct_0212c7c8 {
    /* 0 */ u8 unk_0; // number of players
    /* 1 */ u8 unk_1[5];
    /* 6 */ u8 unk_6;
};
extern UnkStruct_0212c7c8 data_0212c7c8;
extern u16 data_0212c584[4];

#endif
