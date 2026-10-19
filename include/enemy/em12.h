#ifndef UNKNOWN_WIP_A_EM12_H
#define UNKNOWN_WIP_A_EM12_H

#include "engine/entity.h"
#include "engine/player.h"

// Em12 actor fields (file-local overlay for src/enemy/em12.c)
typedef union Em12Word70 {
    u32 typeBits; // ParseTypeBits(e->type), tested against em12_typeMasks[e->areaIndex]
    struct {
        u8 flag;   // set and cleared by em12_move / em12_return
        u8 inArea; // 0xff while a player stands inside the area box
        u8 walkState; // bit flags set by igoalWalk
        u8 unk_73;
    } b;
} Em12Word70;

typedef struct Vars_Em12 {
    /* 00 */ u8 unk_00[0x58];
    /* 58 */ Entity *target;      // player the actor aims at
    /* 5c */ u8 unk_5c[0x14];
    /* 70 */ Em12Word70 w70;
    /* 74 */ s16 homeX;           // spawn position (x.HI) after em12_init
    /* 76 */ s16 homeY;           // spawn position (y.HI) after em12_init
    /* 78 */ u16 areaX;           // area box origin and size (guessed)
    /* 7a */ u16 areaY;
    /* 7c */ u16 areaW;
    /* 7e */ u16 areaH;
} Vars_Em12;
#define V(e) VARS(Vars_Em12, e)

typedef struct UnkStruct_0212c648 {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 unk_18;
    /* 1a */ u16 unk_1a;
} UnkStruct_0212c648;

extern UnkStruct_0212c648 data_0212c648;
extern u16 data_0212c5bc;          // frame counter
extern u32 em12_typeMasks[];
extern u16 data_0213492c[];
extern u16 em12_spawnOffsetY[];
extern const u8 em12_hitbox[];
extern const s8 em12_kemuriOffsets[];
extern const s8 em12_walkOffsets[];
extern const u16 data_020d2144[];
extern u8 *data_02171e0c;
extern u16 data_0212c584[4];
extern const u8 em12_colorByPlayer[];


#endif
