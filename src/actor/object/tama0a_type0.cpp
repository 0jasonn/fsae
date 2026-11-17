#include "engine/functions.h"
#include "ui/stagesel_common.h"
#include "global.h"

// tama0a_type0_init (0x0207cb58): starts the type 0 shot. With type2 set it flies at a fixed speed; otherwise it aims
// at a random player.
void tama0a_type0_init(Entity *e) {
    e->action = 1;
    e->spriteSettings.b0 = 1;
    e->unk_2e = 2;
    e->y.WORD += 1;
    e->z.HALF.HI -= 0x1a;
    e->hitbox = data_020dca68;
    e->unk_5e.b0 = 3;
    if (e->type2 != 0) {
        e->speed = 0x1c0;
    } else {
        u32 index = Random() % gameState.playerCount;
        e->direction = GetFacingDirection(e, playerWork[index].entity);
        e->speed = 0x180;
    }
    InitAnimationForceUpdate(e, 0);
    EnqueueSFX(0x9d);
}

// tama0a_type0_move (0x0207cc1c): the shot flies, its height rises by 2 per frame. On landing (height >= 0) it spawns
// the ground effect and, for type2 0, four shots in the odd directions of a random quadrant, then removes itself.
void tama0a_type0_move(Entity *e) {
    MoveDir(e);
    UpdateAnimationSingleFrame(e);
    e->z.HALF.HI += 2;
    if (e->z.HALF.HI < 0) {
        return;
    }
    e->z.HALF.HI = 0;
    Entity *effect = GetSetWork(0xf, 6, 0);
    if (effect != NULL) {
        ObjPosCopy(e, effect);
        if (e->type2 != 0) {
            effect->type2 = 0x40;
            SoundReq(0xc4);
        }
    }
    if (e->type2 == 0) {
        u8 base = ((Random() & 3) << 1) + 1;
        u16 i;
        for (i = 0; i < 4; i++) {
            Entity *shot = GetTamaWork(0xb);
            if (shot != NULL) {
                shot->type = 1;
                shot->direction = base + i * 8;
                ObjPosCopy(e, shot);
            }
        }
    }
    PutObjWork(e);
}
