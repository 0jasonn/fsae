#include "engine/functions.h"
#include "enemy/enemycommon.h"
#include "enemy/ending.h"
#include "global.h"

// Implementer B, round 6: EnemyInit (0x020458f8), unmangled in the original, and the enemy helpers after it.

typedef int (*GetVGroupResultFunc)(Entity *, u16);

ARM BOOL EnemyInit(Entity *e) {
    const u16 *row;
    if (e->unk_19 & 1) {
        return FALSE;
    }
    row = enemyInitTable + e->objId * 8;
    if (row[0] == 0xffff) {
        row = enemyInitIndirect[row[1]] + e->type * 8;
    }
    if (row[0] != 0) {
        if (row[0] & 0x8000) {
            e->unk_20 = (u8)row[0];
            {
                u8 bits = (row[0] & 0x300) >> 8;
                e->spriteSettings.b6 = bits;
            }
        } else {
            if (((GetVGroupResultFunc)GetVGroup)(e, row[0])) {
                return TRUE;
            }
        }
    }
    if (row[1] & 0x8000) {
        if (row[1] != 0x80ff) {
            e->spriteSettings.b20 = row[1];
            e->spriteSettings.b16 = e->spriteSettings.b20;
        }
    } else {
        e->spriteSettings.b20 = GetObjColor(row[1] & 0xff);
        e->spriteSettings.b16 = e->spriteSettings.b20;
    }
    e->unk_19 = 1;
    e->unk_1b = (u8)row[2];
    {
        u8 statusBits = (row[3] & 0x8000) >> 8;
        e->statusFlags = statusBits | 9;
    }
    e->unk_40 = (u8)row[3];
    e->attackKnockback = (row[3] & 0x7f00) >> 8;
    e->attackDamage = (row[4] & 0xff00) >> 8;
    e->health = (u8)row[4];
    if (e->speed == 0) {
        e->speed = row[5];
    }
    e->poseId = (u8)row[6];
    e->unk_5c = row[7];
    e->unk_23 = 0;
    func_0208ae78(e);
    return FALSE;
}

// EmCharDir2 (0x02045a8c): the high nibble of a direction byte, or 0xff when the low nibble is clear.
ARM u8 EmCharDir2(u8 a) {
    if ((a & 0xf) != 0) {
        return (u8)(a >> 4);
    }
    return 0xff;
}

// EmCharDir4 (0x02045aa0): quarter direction of a byte, 0xff for the value 4 in the low three bits.
ARM u8 EmCharDir4(u8 a) {
    if ((a & 7) != 4) {
        return (u8)(((a + 4) & 0x1f) >> 3);
    }
    return 0xff;
}

// EmDie (0x02045ac0): spawns the death child of the enemy (or marks an existing one) and puts the enemy away.
ARM void EmDie(Entity *e) {
    Entity *child;
    if (e->unk_6a != 0) {
        if (e->unk_6a & 0x80) {
            return;
        }
        child = GetSetWork(1, e->objId, e->unk_6a);
        if (child == NULL) {
            return;
        }
        ObjPosCopy(e, child);
        child->child = e;
        e->unk_6a |= 0x80;
        return;
    }
    if ((e->contactFlags & 0x7f) != 0x13) {
        child = GetSetWork(1, e->objId, 0);
        if (child != NULL) {
            ObjPosCopy(e, child);
            child->timer = e->unk_16;
            if (data_0212c540[1] == 1) {
                child->type2 |= 0x80;
            }
        }
    }
    PutObjWork(e);
}

// EmPalamCopy (0x02045b74): copies the placement and scroll fields of src into dst.
ARM void EmPalamCopy(Entity *src, Entity *dst) {
    dst->unk_19 = src->unk_19 & 0xfe;
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
    dst->layer = src->layer;
    dst->areaIndex = src->areaIndex;
    dst->linkedEntity = src->linkedEntity;
    dst->unk_64[4] = src->unk_64[4];
    dst->unk_64[5] = src->unk_64[5];
    dst->unk_6b = src->unk_6b;
    *(u16 *)&dst->unk_6c[0] = *(u16 *)&src->unk_6c[0];
}

// EmGetTama (0x02045bd4): takes a free object, sets it up as a bullet of this enemy and registers it.
ARM Entity *EmGetTama(Entity *e, u8 kind, u8 flags) {
    Entity *tama = GetObjWork();
    if (tama != NULL) {
        tama->objKind = 4;
        tama->objId = kind;
        tama->type = flags;
        ObjPosCopy(e, tama);
        RegistObjWork(5, tama);
    }
    return tama;
}

// EmDivPosSet (0x02045c20): copies the enemy's position to two pieces and nudges them apart by 6 units.
ARM void EmDivPosSet(Entity *e, Entity *first, Entity *second) {
    if (first != NULL) {
        EmPalamCopy(e, first);
        if (func_02083d18(first, 6, 0) == 0) {
            if (first->x.HALF.HI + 6 < data_0212c648.unk_28) {
                first->x.HALF.HI = first->x.HALF.HI + 6;
            }
        }
    }
    if (second == NULL) {
        return;
    }
    EmPalamCopy(e, second);
    if (func_02083d18(second, -6, 0) != 0) {
        return;
    }
    if (first->x.HALF.HI - 6 >= 0) {
        second->x.HALF.HI = second->x.HALF.HI - 6;
    }
}
