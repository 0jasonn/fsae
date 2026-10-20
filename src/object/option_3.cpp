#include "object/option.h"

// Option panel screen, third unit (module option). Address -> name:
//   0x0205c2d8 copy_move, 0x0205c330 copy_hide, 0x0205c364 miniPanelPatSet
//   0x0205c3bc panel_mode, 0x0205c3d8 mode_init, 0x0205c3f4 mode_wait, 0x0205c420 mode_out, 0x0205c488 mode_in

ARM void copy_move(Entity *e) {
    Vars_Option *vars = VARS(Vars_Option, e);

    miniPanelPatSet(e);
    if (e->subtimer == data_021349c0[NP_PHASE]) {
        return;
    }
    vars->animBounds[0] = e->x.HALF.HI;
    vars->animBounds[1] = 0xc0;
    ObjAnimMoveSet(e, vars->animBounds, 0x14);
    e->action = 3;
    data_021349c0[NP_SHOWN] = 1;
}

ARM void copy_hide(Entity *e) {
    data_021349c0[NP_SHOWN] = 1;
    miniPanelPatSet(e);
    if (ObjAnimMoveLine(e)) {
        e->action = 1;
        data_021349c0[NP_HIDE_DONE] = 1;
    }
}

ARM void miniPanelPatSet(Entity *e) {
    Vars_Option *vars = VARS(Vars_Option, e);

    if (data_021349c0[NP_SLOT_B] == 3 && e->type2 == data_021349c0[NP_CURSOR_TYPE]) {
        star_adjust(e, -33, -10);
        vars->patSelect = 0;
    } else {
        vars->patSelect = 1;
    }
    e->unk_21 = vars->patBase + vars->patSelect;
}

ARM void panel_mode(Entity *e) {
    panel_mode_actions[e->action](e);
}

ARM void mode_init(Entity *e) {
    e->action = 1;
    e->type2 = 0xff;
    e->timer = 0x20;
}

ARM void mode_wait(Entity *e) {
    if (e->type2 != data_021349c0[NP_PHASE]) {
        e->type2 = data_021349c0[NP_PHASE];
        e->action = 2;
        data_021349c0[NP_SHOWN] = 1;
    }
}

ARM void mode_out(Entity *e) {
    if (DISP_REG(0xc) < 0x20) {
        DISP_REG(0xc) += 2;
    } else {
        void *instance = KnifeApp_getInstance();
        u8 *resource = KnifeApp_getZeldaResource_08ddcc(instance, data_02171d20[data_021349c0[NP_PHASE]]);
        MI_UncompressLZ16(resource, (void *)0x0600e000);
        e->action = 3;
    }
    data_021349c0[NP_SHOWN] = 1;
}

ARM void mode_in(Entity *e) {
    if (DISP_REG(0xc) != 0) {
        DISP_REG(0xc) -= 2;
    } else {
        DISP_REG(0xc) = 0;
        e->action = 1;
    }
    data_021349c0[NP_SHOWN] = 1;
}
