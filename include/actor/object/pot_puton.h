#ifndef WIP_C_POT_PUTON_H
#define WIP_C_POT_PUTON_H

#include "engine/entity.h"

// Local player index (0x0212c504); same declaration as in misc_d.h
extern u8 localPlayerIndex;
extern u16 playerKeys[]; // per-player key state, indexed by player
extern u8 pot_putonLimit;   // 0x021158f0, subtimer limit of a pot being carried

// Bit layout of PlayerData::paletteBits (0x8b): the low two bits are tested here (proposed bitfield for the shared struct)
typedef struct PaletteBitsView {
    u8 low : 2;
    u8 rest : 6;
} PaletteBitsView;

typedef struct Vars_PotPuton {
    /* 00 */ u8 unk_00[0x66];
    /* 66 */ u16 heldKeys;
} Vars_PotPuton;

extern "C" {
void pot_ware(Entity *e);   // 0x0205ee7c
void pot_remove(Entity *e); // 0x0205eefc
}
extern "C" u32 m4aSongNumIsPlaying(u16 song);
void pot_clash(Entity *e, Entity *other); // 0x0205f224

#endif
