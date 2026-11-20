#ifndef ACTOR_OBJECT_POT_PUTON_H
#define ACTOR_OBJECT_POT_PUTON_H

#include "engine/entity.h"

// Local player index (0x0212c504); same declaration as in misc_d.h
extern u8 pot_putonLimit;   // 0x021158f0, subtimer limit of a pot being carried

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
