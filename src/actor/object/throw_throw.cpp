#include "engine/functions.h"
#include "global.h"
#include "actor/object/throw_throw.h"

// throw_throw (0x02080560, symbol throw_throw_080560): the Throw actor carrying its child (the thrown object) through
// the air. While it flies it moves, follows the cell walls and falls; on landing it breaks, bounces or stops; while
// it has no speed yet it waits for the player to let go.
void throw_throw_080560(Entity *e) {
    Entity *owner;
    Entity *thrown;
    Entity *spawned;
    int kind;
    u16 cell;

    thrown = e->child;
    owner = playerWork[e->type].entity;
    if (thrown->action != 2) {
        func_020841b0(e);
        PutObjWork(e);
        return;
    }
    if (e->contactFlags & 0x80) {
        e->direction = 0xff;
    }
    if (e->speed != 0) {
        if (e->unk_42 & 0x80) {
            e->unk_42 = 0;
            e->direction = e->baseDirection;
        }
        if (thrown->objKind == 1 || thrown->objKind == 3) {
            func_020852ec(e);
            if (thrown->objKind == 1) {
                if (func_02083ccc(e, data_020dd038[e->direction >> 2], data_020dd038[(e->direction >> 2) + 1]) == 0x2d) {
                    e->direction = 0xff;
                }
                if (func_02083ccc(thrown, 0, 0) == 6) {
                    spawned = GetSetWork(0x39, 0, 0);
                    if (spawned != NULL) {
                        cell = (thrown->x.HALF.HI >> 4) | ((thrown->y.HALF.HI >> 4) << 6);
                        spawned->x.HALF.HI = ((cell & 0x3f) << 4) | 8;
                        spawned->y.HALF.HI = ((cell & 0xfc0) >> 2) | 8;
                        spawned->layer = thrown->layer;
                    }
                }
            }
        } else if (func_02083ccc(e, data_020dd038[e->direction >> 2], data_020dd038[(e->direction >> 2) + 1]) == 0x47) {
            MoveDir(e);
        } else if (!Check1BlockOshiYoyaku((e->x.HALF.HI >> 4) | (((e->y.HALF.HI + 6) >> 4) << 6), e->layer)) {
            kind = func_02083d28(e);
            if (kind != 0x24 && kind != 0x26) {
                func_020852ec(e);
            }
        }
        if (UpdateGravity(e, 0x2000) == 0) {
            thrown->zVelocity = e->zVelocity;
            thrown->x.WORD = e->x.WORD;
            thrown->y.WORD = e->y.WORD;
            thrown->z.WORD = e->z.WORD;
            kind = func_02083d18(e, 0, 3);
            switch (kind) {
            case 0x20:
            case 0x21:
            case 0x24:
            case 0x25:
                if (thrown->objKind != 1) {
                    e->y.HALF.HI += 3;
                    switch (kind) {
                    case 0x21:
                        EffectSet(e, 0, 0);
                        break;
                    case 0x25:
                        EffectSet(e, 0xc, 0);
                        break;
                    case 0x20:
                    case 0x24:
                        EffectSet(e, 0xb, 0);
                        break;
                    }
                    thrown->subAction = 4;
                } else {
                    thrown->subAction = 3;
                }
                func_020841b0(e);
                PutObjWork(e);
                break;
            default:
                if (e->child == e) {
                    if (e->type2 != 0) {
                        if (e->type2 == 0xf) {
                            EffectSet(e, e->timer, 0x80);
                        } else {
                            spawned = GetObjWork();
                            if (spawned != NULL) {
                                spawned->objId = e->type2;
                                spawned->objKind = 6;
                                spawned->type = e->timer;
                                spawned->x.WORD = e->x.WORD;
                                spawned->y.WORD = e->y.WORD;
                                spawned->z.WORD = e->z.WORD;
                                RegistObjWork(6, spawned);
                            }
                        }
                    }
                    func_020841b0(e);
                    PutObjWork(e);
                } else if (e->timer != 0 || (thrown->objKind == 6 && thrown->objId == 5)) {
                    if (e->timer == 1) {
                        func_02085f98(owner, 0xa);
                    }
                    thrown->subAction = 3;
                    func_0208ae78(e);
                    thrown->spriteSettings.b14 = e->spriteSettings.b14;
                    thrown->spriteSettings.b30 = e->spriteSettings.b30;
                    func_020841b0(e);
                    PutObjWork(e);
                } else {
                    func_02085f98(owner, 0xa);
                    e->timer++;
                    e->zVelocity = 0x10000;
                    e->speed >>= 1;
                }
                break;
            }
            if (thrown->objKind == 1) {
                cell = GetCellKind(((thrown->x.HALF.HI - mapState.originX) >> 4) |
                                       (((thrown->y.HALF.HI - mapState.originY) >> 4) << 6),
                                   thrown->layer);
                if (func_02083e54(cell) == 0x43 && cell != ((PalBits *)&playerWork[thrown->type].paletteBits)->b + 0x176) {
                    playerWork[thrown->type].unk_32 = 1;
                }
            }
        } else {
            func_02086168(e);
            ObjLiftPrioCheck(e);
            thrown->x.WORD = e->x.WORD;
            thrown->y.WORD = e->y.WORD;
            thrown->z.WORD = e->z.WORD;
            thrown->layer = e->layer;
            thrown->spriteSettings.b30 = e->spriteSettings.b30;
            thrown->spriteSettings.b14 = e->spriteSettings.b14;
            if (thrown->layer & 0x4000) {
                cell = GetCellKind((thrown->x.HALF.HI >> 4) | (((thrown->y.HALF.HI + 0xf) >> 4) << 6), thrown->layer);
                if (func_02083ccc(thrown, 0, 0xf) == 0x4009 || (cell >= 0x109 && cell <= 0x10c)) {
                    thrown->spriteSettings.b14 = thrown->spriteSettings.b30 = 2;
                }
            }
            thrown->zVelocity = e->zVelocity;
            thrown->direction = e->direction;
        }
    } else if (owner->frame & 1) {
        func_02085f98(playerWork[e->type].entity, 0xc2);
        throwinit(e);
    } else if (playerWork[e->type].specialState == 0 || VARS(Vars_ThrowOwner, owner)->liftState != 0) {
        throwinit(e);
        e->direction = 0xff;
        e->zVelocity = 0;
    }
}
