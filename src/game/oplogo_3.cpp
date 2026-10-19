#include "engine/functions.h"
#include "global.h"

// Opening logo "you" and button objects, 0x02068494 to 0x020686a0 + 0x74 (you_move .. button_move).
typedef struct Vars_You {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u16 moveCounter; // 16-bit movement counter, indexes the sine table
} Vars_You;
typedef struct BlendRequestOpl {
    /* 00 */ u8 unk_00[7];
    /* 07 */ u8 blendColor;
    /* 08 */ u8 unk_08[4];
    /* 0c */ s32 resetValue;
} BlendRequestOpl;
extern BlendRequestOpl data_0212c5ac;
extern const s16 data_020c91fc[][2];
extern const u8 oplogo_youPosTable[];
extern EntityFunc oplogo_buttonTable[];
extern u8 localPlayerIndex;
extern u8 data_021349c0[];
extern u8 data_0212c4dc;

ARM void you_move(Entity *e) {
    u16 counter;
    s32 sine;
    u8 type;
    UpdateAnimationSingleFrame(e);
    counter = VARS(Vars_You, e)->moveCounter;
    sine = data_020c91fc[counter >> 4][0];
    type = e->type2;
    e->x.HALF.HI = oplogo_youPosTable[type * 2] + ((s32)(((s64)sine * (-1 << 18) + 0x800) >> 12) >> 12);
    e->y.HALF.HI = oplogo_youPosTable[type * 2 + 1] + ((s32)(((s64)sine * -0x5a000 + 0x800) >> 12) >> 12);
    switch (e->timer) {
    case 0:
        VARS(Vars_You, e)->moveCounter = counter + 0x33;
        if (VARS(Vars_You, e)->moveCounter >= 0x500) {
            e->timer = e->timer + 1;
        }
        break;
    case 1:
        VARS(Vars_You, e)->moveCounter = counter + 0x25c;
        if (VARS(Vars_You, e)->moveCounter >= 0x4000) {
            VARS(Vars_You, e)->moveCounter = 0x4000;
            e->action++;
            e->timer = 0xa;
        }
        break;
    }
    switch (e->subtimer) {
    case 0x1e:
        data_0212c5ac.resetValue = -27;
        data_0212c5ac.blendColor = 0;
        FadeSet(3, 0xc);
        break;
    case 0x28:
        data_0212c5ac.resetValue = -27;
        data_0212c5ac.blendColor = 0;
        FadeSet(5, 0xc);
        break;
    }
    e->subtimer++;
}

ARM void oplogo_you_flash(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        return;
    }
    PutObjWork(e);
}

ARM void oplogo_button(Entity *e) {
    oplogo_buttonTable[e->action](e);
}

ARM void button_init(Entity *e) {
    u8 action = e->action;
    e->action = action + 1;
    e->x.HALF.HI = 0x100;
    e->y.HALF.HI = 0xc0;
    e->unk_1b = 0x6b;
    e->unk_20 = 0x80;
    *(u32 *)&e->spriteSettings |= 0x2000;
    e->spriteSettings.b14 = 0;
    e->spriteSettings.b30 = 0;
    e->spriteSettings.b6 = 2;
    e->spriteSettings.b16 = 7;
    InitAnimationForceUpdate(e, 0);
}

ARM void button_move(Entity *e) {
    u8 value;
    if (localPlayerIndex == 0) {
        if ((data_021349c0[8] & 0x80) && data_0212c4dc == 4) {
            value = 2;
        } else {
            value = 0;
        }
        e->spriteSettings.b0 = value;
        UpdateAnimationSingleFrame(e);
    } else {
        e->spriteSettings.b0 = 0;
    }
}
