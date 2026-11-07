#include "actor/object/frontcheck_a.h"

// What is in front of an actor that pushes/uses (FrontCheck, 0x02022e1c): looks at the map cell the actor faces and
// reacts to keys, doors, chests and pushable blocks. Returns 0 for nothing, 1 for a door/chest, 2 for a push.
int FrontCheck(Entity *e, PlayerData *player) {
    int buf;
    const DirDelta *delta;
    u16 cell;
    u16 kind;
    u16 cls;
    u8 attr;
    int next;
    u16 cellNext;
    int i;
    int count;
    u8 blocked;
    Entity *obj;
    Entity *spawn;
    u8 attr2;
    volatile s16 step2; // lives on the stack in the original
    s16 stepNow;
    int i2;
    int count2;
    u8 blocked2;

    buf = GetBgBuffAdrs(e->layer);
    delta = (const DirDelta *)((u8 *)data_020cd6c4 + ((e->animationState & 6) << 1));
    cell = (u16)(((e->x.HALF.HI + delta->x - mapState.scrollX) >> 4)
                 | (((e->y.HALF.HI + delta->y - mapState.scrollY) >> 4) << 6));
    kind = GetCellKind(cell, e->layer);
    cls = func_02083e54(kind);
    switch (cls) {
    case 0x4002:
        if (player->unk_35 & 0x80) {
            break;
        }
        if (e->frame == 0) {
            break;
        }
        next = cell + *(s16 *)((u8 *)cellDeltaTable + (e->animationState & ~1));
        attr = *(u8 *)(buf + next + 0x2004);
        cls = func_02083e54(GetCellKind((u16)next, e->layer));
        if ((attr == 0 || attr >= 0x20) && cls != 0x58) {
            ((u16 *)(buf + (cell << 1)))[2] = 0x4000 + 3 + (e->animationState >> 1);
            player->unk_06 = 0xa0;
            player->state = 5;
            player->statusFlags |= 1;
            e->x.HALF.LO = 0;
            e->y.HALF.LO = 0;
            e->direction = e->animationState << 2;
        }
        return 2;
    case 0x3b:
        if (player->unk_35 & 0x80) {
            break;
        }
        if (e->frame == 0) {
            break;
        }
        if (!TryUsingKey(e)) {
            break;
        }
        if ((e->layer >> 14) != 2) {
            RewCell(0x2f, cell, 0x4000);
        } else {
            RewCell(0x58, cell, 0x8000);
        }
        spawn = GetSetWork(0xf, 2, 0);
        if (spawn != NULL) {
            ObjPosCopy(e, spawn);
            spawn->x.HALF.HI += delta->x;
            spawn->y.HALF.HI += delta->y;
        }
        break;
    case 0x3a:
        if (player->unk_35 & 0x80) {
            break;
        }
        if (e->frame == 0) {
            break;
        }
        SetMoveBlockByKind(e, (u8)(player->unk_35 << 2), kind, cell);
        return 2;
    case 0x5c:
        if (player->unk_35 & 0x80) {
            break;
        }
        if (!TryUsingKey(e)) {
            break;
        }
        openDoor(e, player, buf);
        return 1;
    case 0x2a:
        if (!(data_0212c510 & 1)) {
            break;
        }
        if (e->animationState != 0) {
            break;
        }
        obj = player->entity;
        cellNext = (u16)(((obj->x.HALF.HI - mapState.scrollX) >> 4) | (((obj->y.HALF.HI - mapState.scrollY) >> 4) << 6));
        kind = GetCellKind(cellNext, obj->layer);
        if (func_02083e54(kind) == 0x43) {
            if (kind != ((PalBits *)&playerWork[e->type].paletteBits)->b + 0x176) {
                break;
            }
        }
        data_0212ceca[e->type * 0x94] = 1;
        TakaraOpen(e, cell, e->layer);
        return 1;
    case 0x4009:
        step2 = *(s16 *)((u8 *)cellDeltaTable + (e->animationState & ~1));
        if (!(player->unk_35 & 0x80) && e->frame != 0) {
            cellNext = (u16)(cell + step2);
            cls = func_02083e54(GetCellKind(cellNext, e->layer));
            if (cls == 0x48 || cls == 0x49 || cls == 0x58) {
                break;
            }
            count = gameState.playerCount;
            blocked = *(u8 *)(buf + cellNext + 0x2004);
            for (i = 0; i < count; i++) {
                obj = playerWork[i].entity;
                if (obj != NULL) {
                    if (cellNext == (u16)(((obj->y.HALF.HI >> 4) * 64) + (obj->x.HALF.HI >> 4))) {
                        blocked = 1;
                        break;
                    }
                }
            }
            if (blocked != 0) {
                break;
            }
            ((u16 *)(buf + (cell << 1)))[2] = 0x4000 + 0xa + (e->animationState >> 1);
            player->unk_06 = 0xa0;
            player->state = 5;
            player->statusFlags |= 1;
            e->x.HALF.LO = 0;
            e->y.HALF.LO = 0;
            e->direction = e->animationState << 2;
            return 2;
        }
        if (player->specialState != 1) {
            break;
        }
        if (e->frame == 0) {
            break;
        }
        stepNow = step2;
        cellNext = (u16)(cell - stepNow);
        step2 = (u16)(cellNext - stepNow);
        cls = func_02083e54(GetCellKind(cellNext, e->layer));
        if (cls == 0x48 || cls == 0x49 || cls == 0x58) {
            break;
        }
        count2 = gameState.playerCount;
        blocked2 = *(u8 *)(buf + cellNext + 0x2004);
        attr2 = *(u8 *)(buf + (u16)step2 + 0x2004);
        for (i2 = 0; i2 < count2; i2++) {
            obj = playerWork[i2].entity;
            if (obj != NULL && &playerWork[i2] != player && !((PalBits *)&playerWork[i2].paletteBits)->d) {
                if (cellNext == (u16)(((obj->y.HALF.HI >> 4) * 64) + (obj->x.HALF.HI >> 4))) {
                    blocked2 = 1;
                    break;
                }
            }
        }
        if (blocked2 != 0 || attr2 != 0) {
            break;
        }
        ((u16 *)(buf + (cell << 1)))[2] = *(const u16 *)((const u8 *)data_020cd6b0 + (e->animationState & ~1));
        player->state = 0x10;
        player->stateTimer = 0x20;
        player->statusFlags |= 1;
        e->x.HALF.LO = 0;
        e->y.HALF.LO = 0;
        return 2;
    }
    return 0;
}
