#include "engine/functions.h"
#include "global.h"
#include "actor/object/setcommon.h"
#include "actor/object/set48_actions.h"

// Set48 switch actor (module set48). Address -> name:
//   0x0206f5a8 set48_move2 (original name)

typedef struct Vars_Set48Switch {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits;   // ParseTypeBits(type), tested against em12_typeMasks[area]
    /* 64 */ u8 unk_64[0x14];
    /* 78 */ u32 lastMasks;  // area flags as last seen by this actor
    /* 7c */ u32 selectMask; // flag bits this switch may set when hit (guess)
} Vars_Set48Switch;
#define SWITCH(e) VARS(Vars_Set48Switch, e)

// When hit, merges its bits into the area flags; whenever the flags of its type bits change, updates the palette
// of the sprite and plays the sound.
void set48_move2(Entity *e) {
    if (e->contactFlags & 0x80) {
        em12_typeMasks[e->areaIndex] =
            SWITCH(e)->typeBits ^ (em12_typeMasks[e->areaIndex] & ~(SWITCH(e)->selectMask ^ SWITCH(e)->typeBits));
        SWITCH(e)->lastMasks = em12_typeMasks[e->areaIndex];
        e->spriteSettings.b16 = (SWITCH(e)->typeBits & em12_typeMasks[e->areaIndex]) ? 0x8001 : 0x8000;
        e->iframes = 0xe8;
        EnqueueSFX(0x16);
    }
    if (((SWITCH(e)->lastMasks ^ em12_typeMasks[e->areaIndex]) & SWITCH(e)->typeBits) == 0) {
        return;
    }
    e->spriteSettings.b16 = (SWITCH(e)->typeBits & em12_typeMasks[e->areaIndex]) ? 0x8001 : 0x8000;
    SWITCH(e)->lastMasks = em12_typeMasks[e->areaIndex];
    EnqueueSFX(0x16);
}
