#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "game/wanwan.h"

// Wanwan module, 0x0208139c: wanwan_init sets up a chain piece that follows the player entity data_0212ceb0[type].

extern const u8 wanwan_hitbox[]; // wanwan_hitbox, rename in renames.txt

// wanwan_init (0x0208139c)
ARM void wanwan_init(Entity *e) {
    Entity *owner;
    Entity *child;
    void *resource;
    s32 resourceSize;
    void *app;

    owner = data_0212ceb0[e->type].entity;
    e->action++;
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b16 = 4;
    e->unk_1b = 9;
    e->speed = 0x180;
    e->x.WORD = owner->x.WORD;
    e->y.WORD = owner->y.WORD - 1;
    e->z.WORD = owner->z.WORD;
    e->layer = owner->layer | 0xc000;
    e->spriteSettings.b6 = owner->spriteSettings.b6;
    e->unk_20 = owner->unk_20 + 0x10;
    e->spriteSettings.b20 = 1;
    e->spriteSettings.b16 = e->spriteSettings.b20;
    *(u16 *)&e->unk_6a = 0xa00;

    if (e->type2 & 0x80) {
        e->timer = 0x78;
        child = e->child;
        if (child != NULL) {
            child->parent = e;
        }
        e->spriteSettings.b14 = owner->spriteSettings.b14 - 1;
        e->spriteSettings.b30 = 1;
        e->attackDamage = 10;
        e->attackKnockback = 15;
        e->unk_40 = 0x13;
        e->poseId = 0x1d;
        e->statusFlags = (owner->statusFlags + 1) & 0x7f;
        e->unk_5c = owner->unk_5c;
        e->hitbox = wanwan_hitbox;
        func_02084180(e);
        e->unk_2e = 4;
        InitAnimationForceUpdate(e, 0xb);
        app = KnifeApp_getInstance();
        resource = KnifeApp_getZeldaResource_08dde0(app, &resourceSize, 0x98);
        func_020845b0(0x6400200 + ((u32)e->type << 10), resource, (u16)resourceSize);
        EnqueueSFX(0x51);
    } else {
        e->spriteSettings.b14 = owner->spriteSettings.b14;
        e->unk_5e.b0 = 0;
        e->spriteSettings.b30 = owner->spriteSettings.b30;
        InitAnimationForceUpdate(e, 0xd);
    }

    if (e->type2 < 5) {
        child = GetObjWork();
        e->child = child;
        if (child != NULL) {
            child->parent = e;
            e->child->objId = 0x10;
            e->child->objKind = 8;
            e->child->type = e->type;
            e->child->type2 = e->type2 + 1;
            if (e->type2 == 4) {
                e->child->type2 |= 0x80;
                data_0212ceb0[e->type].unk_3d[0] = 1;
            }
            RegistObjWork(6, e->child);
        }
    }
    if (e->type2 == 0) {
        e->parent = owner;
    }
}
