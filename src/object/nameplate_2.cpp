#include "engine/functions.h"
#include "global.h"
#include "object/fdecls.h"

// Name plate actor, second unit (module nameplate). Address -> name:
//   0x0205ba4c namePlate_appear, 0x0205bb1c namePlate_move, 0x0205bc48 namePlate_entry
//   (namePlate itself is in nameplate.cpp; namePlate_init at 0x0205b9c0 is in scratch/agentF/nonmatching)

// data_021349c0 bytes used by the name plate code
enum {
    NP_PHASE = 0x1a,   // == 3 while the plate is set up
    NP_SHOWN = 0x1b,   // set to 1 once the plate is shown
    NP_SLOT_A = 0x1e,  // slot index of the first plate
    NP_SLOT_B = 0x1f,  // slot index of the second plate
    NP_FLAG_24 = 0x24, // nonzero: plate is drawn at the second position
};

typedef struct Vars_NamePlate {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u8 unk_64[3];
    /* 67 */ u8 hideMask; // set to 0xff on init
} Vars_NamePlate;

extern u8 data_021349c0[];
extern u8 multiSioSelect[];
extern const u8 data_020d8aa4[];  // animation flags, indexed by timer * 3 + type2
extern const u16 data_020d8bae[]; // bounds for the appear animation, 4 bytes per mask
extern const u16 data_020d8ae0[]; // bounds for the move animation, 4 bytes per index
extern u16 data_0212c75c[];       // display shadow, halfword registers
extern const u8 namePlateSetTable[]; // namePlateSetTable, table passed to SetTblSetWorks

ARM void namePlate_appear(Entity *e) {
    Vars_NamePlate *vars = VARS(Vars_NamePlate, e);

    if (vars->hideMask == 0xff) {
        if (e->timer != 3) {
            if (e->timer != 4) {
                vars->hideMask = e->timer;
            }
        } else {
            { int base = (multiSioSelect[4] + 1) * 3; vars->hideMask = base + e->type2; }
        }
        if (vars->hideMask != 0xff) {
            ObjAnimMoveSet(e, &data_020d8bae[vars->hideMask * 2], data_020d8aa4[e->timer * 3 + e->type2]);
            e->timer++;
        } else {
            e->action++;
            if (e->child != NULL) {
                e->child->subAction++;
            }
        }
    }
    if (ObjAnimMoveLine(e)) {
        vars->hideMask = 0xff;
    }
}

ARM void namePlate_move(Entity *e) {
    u8 index;
    u8 target;

    if (data_021349c0[NP_SLOT_A] == e->type2) {
        index = 3;
    } else if (data_021349c0[NP_SLOT_B] == e->type2) {
        index = 4;
    } else {
        index = 6;
    }
    e->spriteSettings.b16 = index;
    ObjAnimMoveLine(e);
    e->spriteSettings.b14 = 3;
    if (data_021349c0[NP_SLOT_B] == e->type2) {
        if (data_021349c0[NP_FLAG_24] != 0) {
            e->spriteSettings.b14 = 0;
        }
        star_adjust(e, 0, 0xc);
    }
    if (data_021349c0[NP_SLOT_A] < 3) {
        return;
    }
    if (data_021349c0[NP_PHASE] == 3) {
        data_021349c0[NP_SHOWN] = 1;
        if (data_021349c0[NP_SLOT_B] != e->type2) {
            PutObjWork(e);
            return;
        }
        e->action = 3;
        e->subAction = 0;
        target = 6;
    } else {
        target = e->type2;
        if (data_021349c0[NP_SLOT_B] < e->type2) {
            target = (e->type2 + 3) & 0xff;
        }
    }
    if (target != VARS(Vars_NamePlate, e)->hideMask) {
        VARS(Vars_NamePlate, e)->hideMask = target;
        ObjAnimMoveSet(e, &data_020d8ae0[target * 2], 8);
    }
}

ARM void namePlate_entry(Entity *e) {
    switch (e->subAction) {
    case 0:
        e->spriteSettings.b30 = 0;
        e->spriteSettings.b14 = 1;
        if (ObjAnimMoveLine(e)) {
            e->subAction = 1;
            e->subtimer = 0x20;
            data_0212c75c[0] |= 0x2e00;
            data_0212c75c[0x60 / 2] = 9;
            data_0212c75c[0x62 / 2] = 0x1f40 - 1;
            data_0212c75c[0x58 / 2] = 0x8e8;
            data_0212c75c[0x5c / 2] = 0x3180 - 0x8e8;
            data_0212c75c[0x66 / 2] = 0x8e8 - 0xa4;
            data_0212c75c[0x68 / 2] = 0x8e8 - 0xdc;
            SetTblSetWorks(namePlateSetTable);
        }
        data_021349c0[NP_SHOWN] = 1;
        break;
    case 1:
        if (e->subtimer < 0x98) {
            e->subtimer += 8;
            data_0212c75c[0x5c / 2] = ((u8)e->subtimer << 8) | 0x98;
        } else {
            data_0212c75c[0] &= 0xdfff;
            e->subAction = 2;
        }
        data_021349c0[NP_SHOWN] = 1;
        break;
    default:
        break;
    }
    star_adjust(e, 0, 0xc);
}
