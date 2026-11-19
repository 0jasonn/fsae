#include "engine/functions.h"
#include "global.h"
#include "actor/object/fdecls.h"
#include "actor/object/nameplate.h"
#include "engine/display_state.h"

// Name plate actor, second unit (module nameplate). Address -> name:
//   0x0205ba4c namePlate_appear, 0x0205bb1c namePlate_move, 0x0205bc48 namePlate_entry
//   (namePlate itself is in nameplate.cpp; namePlate_init at 0x0205b9c0 is in scratch/agentF/nonmatching)

#include "engine/effect_state.h"
extern u8 multiSioSelect[];
extern const u8 data_020d8aa4[];  // animation flags, indexed by timer * 3 + type2
extern const u16 data_020d8bae[]; // bounds for the appear animation, 4 bytes per mask
extern const u16 data_020d8ae0[]; // bounds for the move animation, 4 bytes per index
extern const u8 namePlateSetTable[]; // namePlateSetTable, table passed to SetTblSetWorks

void namePlate_appear(Entity *e) {
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

void namePlate_move(Entity *e) {
    u8 index;
    u8 target;

    if (effectState.slotA == e->type2) {
        index = 3;
    } else if (effectState.slotB == e->type2) {
        index = 4;
    } else {
        index = 6;
    }
    e->spriteSettings.b16 = index;
    ObjAnimMoveLine(e);
    e->spriteSettings.b14 = 3;
    if (effectState.slotB == e->type2) {
        if (effectState.panelMode != 0) {
            e->spriteSettings.b14 = 0;
        }
        star_adjust(e, 0, 0xc);
    }
    if (effectState.slotA < 3) {
        return;
    }
    if (effectState.panelPhase == 3) {
        effectState.panelShown = 1;
        if (effectState.slotB != e->type2) {
            PutObjWork(e);
            return;
        }
        e->action = 3;
        e->subAction = 0;
        target = 6;
    } else {
        target = e->type2;
        if (effectState.slotB < e->type2) {
            target = (e->type2 + 3) & 0xff;
        }
    }
    if (target != VARS(Vars_NamePlate, e)->hideMask) {
        VARS(Vars_NamePlate, e)->hideMask = target;
        ObjAnimMoveSet(e, &data_020d8ae0[target * 2], 8);
    }
}

void namePlate_entry(Entity *e) {
    switch (e->subAction) {
    case 0:
        e->spriteSettings.b30 = 0;
        e->spriteSettings.b14 = 1;
        if (ObjAnimMoveLine(e)) {
            e->subAction = 1;
            e->subtimer = 0x20;
            displayState.displayFlags |= 0x2e00;
            displayState.winIn = 9;
            displayState.winOut = 0x1f40 - 1;
            displayState.win0H = 0x8e8;
            displayState.win0V = 0x3180 - 0x8e8;
            displayState.blendCnt = 0x8e8 - 0xa4;
            displayState.blendAlpha = 0x8e8 - 0xdc;
            SetTblSetWorks(namePlateSetTable);
        }
        effectState.panelShown = 1;
        break;
    case 1:
        if (e->subtimer < 0x98) {
            e->subtimer += 8;
            displayState.win0V = ((u8)e->subtimer << 8) | 0x98;
        } else {
            displayState.displayFlags &= 0xdfff;
            e->subAction = 2;
        }
        effectState.panelShown = 1;
        break;
    default:
        break;
    }
    star_adjust(e, 0, 0xc);
}
