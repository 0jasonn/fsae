#include "engine/entity.h"
#include "engine/player.h"
#include "global.h"
#include "object/objprio.h"

// ObjLiftPrioCheck (0x0204ff68). Sets the priority bits of spriteSettings from the map cells under the entity.
// Accept sets b30 = 2 (b14 follows); reject sets b30 = 1.
#define OBJ_LIFT_ACCEPT() \
    do { \
        e->spriteSettings.b30 = 2; \
        e->spriteSettings.b14 = e->spriteSettings.b30; \
        return 1; \
    } while (0)
#define OBJ_LIFT_REJECT() \
    do { \
        e->spriteSettings.b30 = 1; \
        e->spriteSettings.b14 = e->spriteSettings.b30; \
        return 0; \
    } while (0)

ARM int ObjLiftPrioCheck(Entity *e) {
    s32 cell;

    if ((e->layer & 0x8000) == 0) {
        cell = func_02083c8c(e->x.HALF.HI, (s16)(e->y.HALF.HI - 4), 0x8000);
        if (cell != 0) {
            OBJ_LIFT_ACCEPT();
        }
        if (((u8 *)&data_0212c7c8)[1] == 5) {
            cell = func_02083c8c(e->x.HALF.HI, e->y.HALF.HI, e->layer);
            if (cell == 0x264 || cell == 0x273) {
                OBJ_LIFT_ACCEPT();
            }
            cell = func_02083c8c(e->x.HALF.HI, (s16)(e->y.HALF.HI - 4), e->layer);
            switch (cell) {
            case 0x210:
            case 0x21f:
            case 0x2e2:
            case 0x3cf:
            case 0x3d8:
            case 0x40b:
            case 0x414:
                OBJ_LIFT_ACCEPT();
            default:
                break;
            }
            OBJ_LIFT_REJECT();
        }
        cell = func_02083c8c(e->x.HALF.HI, (s16)(e->y.HALF.HI - 4), e->layer);
        switch (cell) {
        case 0x210:
        case 0x21f:
        case 0x264:
        case 0x273:
        case 0x2e2:
        case 0x3cf:
        case 0x3d8:
        case 0x40b:
        case 0x414:
            OBJ_LIFT_ACCEPT();
        default:
            break;
        }
        OBJ_LIFT_REJECT();
    }
    return 0;
}
