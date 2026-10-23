#include "engine/functions.h"
#include "global.h"
#include "object/set3c.h"

// Set3c actor (module set3c). Address -> name:
//   0x0205caf0 Set3c (original name), 0x0205cb54 set3c_init, 0x0205cbec set3c_wait, 0x0205cc3c set3c_move
//   (anacheck at 0x0205ccf8 is in scratch/agentF/nonmatching)

// Actor fields (file-local overlay)
typedef struct Vars_Set3c {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits;      // ParseTypeBits(e->type), tested against em12_typeMasks[areaIndex]
    /* 64 */ u8 unk_64[2];
    /* 66 */ u16 lastDirection; // copy of e->direction, a change plays the sound 0x8c
} Vars_Set3c;

extern u32 em12_typeMasks[];         // per-area type flags
extern const u32 flagBits[];         // flag bit for each type2
extern const EntityFunc data_020d8c18[]; // state table indexed by e->action
extern const u8 data_020d8c04[];     // hitbox of the set3c actor

ARM void Set3c(Entity *e) {
    if (func_02085ccc(e)) {
        if (e->type2 == 0xff) {
            return;
        }
        em12_typeMasks[e->areaIndex] |= flagBits[e->type2];
        return;
    }
    data_020d8c18[e->action](e);
}

ARM void set3c_init(Entity *e) {
    Vars_Set3c *vars = VARS(Vars_Set3c, e);

    if (e->type == 0xff) {
        e->action = 2;
        e->spriteSettings.b0 = 1;
        e->statusFlags = 0x89;
    } else {
        e->action = 1;
        e->statusFlags = 9;
        vars->typeBits = ParseTypeBits(e->type);
    }
    e->poseId = 0x2a;
    e->attackKnockback = 8;
    e->unk_40 = 0x38;
    e->unk_5c = 0x21ff;
    e->hitbox = data_020d8c04;
    InitAnimationForceUpdate(e, 0);
    vars->lastDirection = e->direction;
}

ARM void set3c_wait(Entity *e) {
    Vars_Set3c *vars = VARS(Vars_Set3c, e);

    if ((vars->typeBits & em12_typeMasks[e->areaIndex]) != vars->typeBits) {
        return;
    }
    e->action = 2;
    e->spriteSettings.b0 = 1;
    e->statusFlags |= 0x80;
    SKemuriSet(e);
}

ARM void set3c_move(Entity *e) {
    Vars_Set3c *vars = VARS(Vars_Set3c, e);

    if (e->contactFlags & 0x80) {
        if (e->contactFlags != 0x80) {
            e->unk_42 = (Random() & 7) + 0x40;
        }
        e->direction = e->baseDirection;
        e->iframes = 0;
        e->speed = 0x400;
        EnqueueSFX(0x8c);
    }
    if (e->unk_42 != 0) {
        int next = e->unk_42 - 1;
        if ((u8)next < 0xc) {
            e->speed -= 0x40;
        }
        e->unk_42 = next;
        if (func_020847dc(e) != 0 && e->direction != vars->lastDirection) {
            EnqueueSFX(0x8c);
            vars->lastDirection = e->direction;
        }
        if (anacheck(e)) {
            return;
        }
    }
    UpdateAnimationSingleFrame(e);
}
