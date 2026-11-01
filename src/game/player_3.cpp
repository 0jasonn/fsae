#include "engine/functions.h"
#include "global.h"
#include "engine/misc_d.h"

// pauseState is the pause state block: [0] phase, [1] chosen pause option, [2] delay timer,
// [0xe] reset flag, [0xf] set when the wireless session is being closed

extern u8 pauseState[];
extern u16 data_021355a0;
extern u16 data_0212c58c[];
extern u8 data_0212c4b8;
extern u8 data_0212c4d4;
extern u16 data_0212c520;

#include "engine/player.h"

extern u16 scrollArgs[];
extern u8 objAffineSet[];
extern u8 objAffineSetAlt[];
extern u8 data_0212c4e4;
extern u16 data_0212c514;
extern u16 data_0212c510;
extern Entity *data_0212c534;
extern u16 data_0212c584[];
extern u8 plScratchBuffer[];
extern const EntityFunc entityDispatchTable[];

extern u8 telopRequest[];
extern const u32 data_021186e4[];
extern const u8 data_0212c84c[];

extern const s8 *const data_0211525c[];

extern const VoidFunc rankingStepTable[];
extern u8 localPlayerIndex;

void PlWorkColorReset(void) {
    u8 i;
    PlayerData *end;
    PlayerData *player;

    player = data_0212ceb0;
    end = &data_0212ceb0[4];
    i = 0;
    if (player < end) {
        do {
            player->paletteBits = (player->paletteBits & ~0xc) | ((i & 3) << 2);
            i++;
            player++;
        } while (player < end);
    }
}

// pauseState is the pause state block: [0] phase, [1] chosen pause option, [2] delay timer,
// [0xe] reset flag, [0xf] set when the wireless session is being closed

void PlWeaponFireCheck(Entity *e) {
    s32 contact;
    Entity *target;
    Entity *shot;
    s32 dy;
    s32 dx;

    contact = e->contactFlags;
    if (!(contact & 0x80)) {
        return;
    }
    contact &= 0x7f;
    if (contact == 0xc) {
        return;
    }
    if (contact < 4 || contact > 0x15) {
        return;
    }
    e->contactedEntity->contactFlags = (e->contactedEntity->contactFlags & 0x7f) | 0x40;
    e->poseId = 0xe;
    e->contactedEntity->poseId = 0xe;
    dx = e->x.WORD - e->contactedEntity->x.WORD;
    dy = e->y.WORD - e->contactedEntity->y.WORD;
    shot = GetObjWork();
    if (shot == 0) {
        return;
    }
    shot->objId = 0x17;
    shot->objKind = 6;
    shot->x.WORD = e->x.WORD - (dx >> 1);
    shot->y.WORD = e->y.WORD - (dy >> 1);
    shot->spriteSettings.b14 = e->spriteSettings.b14;
    shot->spriteSettings.b30 = e->spriteSettings.b30;
    shot->layer = e->layer;
    RegistObjWork(6, shot);
}

void PlayerTrans(void) {
    s32 i;

    for (i = 0; i < data_0212c7c8.playerCount; i++) {
        data_0212ceb0[i].entity->y.HALF.HI += data_0212ceb0[i].yOffset;
        if ((u8)(data_0212ceb0[i].specialState + 0xfd) <= 1) {
            if (*(Entity **)&data_0212ceb0[i].entity->unk_6c[0] != 0 && (*(Entity **)&data_0212ceb0[i].entity->unk_6c[0])->child != 0) {
                PlLiftSync(data_0212ceb0[i].entity);
            }
        }
        if (data_0212ceb0[i].statusFlags & 4) {
            func_0208a95c(data_0212ceb0[i].entity);
        }
        if (data_0212ceb0[i].weapon != 0) {
            PlWeaponSync(data_0212ceb0[i].entity, data_0212ceb0[i].weapon);
        }
    }
}
