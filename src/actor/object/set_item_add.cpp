#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/set_item_add.h"

// Actor setup (module set). Address -> name:
//   0x0205784c SetItemAdd (original name): applies the item picked up by a player (hearts, rupees, key, power-ups, ...);
//   in a single-player game the power-up levels are shared by both players.

void SetItemAdd(Entity *item, Entity *player) {
    void *app = KnifeApp_getInstance();
    Entity *e0 = player;
    Entity *e1 = player;
    PlayerData *p0 = NULL;
    PlayerData *p1 = p0;
    Entity *setWork;

    if (player->objKind == 1) {
        if (KnifeApp_isWirelessMode(app) == 0) {
            p1 = &data_0212ceb0[1];
            p0 = &data_0212ceb0[0];
            e0 = p0->entity;
            e1 = data_0212ceb0[1].entity;
        } else {
            p1 = &data_0212ceb0[player->type];
            p0 = p1;
        }
    }
    switch (item->type) {
    case 0:
        if (player->objKind == 1) {
            AddHeart(player, 8);
        } else {
            int health = player->health + 8;
            if (health < 0xff) {
                player->health = health;
            } else {
                player->health = 0xff;
            }
        }
        break;
    case 1:
        if (player->objKind == 1) {
            AddRupee(player, 1);
        }
        break;
    case 2:
        if (player->objKind == 1) {
            AddRupee(player, 5);
        }
        break;
    case 3:
        if (player->objKind == 1) {
            AddRupee(player, 0x14);
        }
        break;
    case 4:
        if (e0->objKind == 1) {
            AddRupeeKakera(e0);
        }
        break;
    case 5:
        if (player->objKind == 1) {
            AddKey(player);
        }
        break;
    case 6:
        if (player->objKind == 1) {
            AddRupee(player, 0x32);
        }
        break;
    case 7:
        if (player->objKind == 1) {
            AddHeart(player, 0x38);
        } else {
            int health = player->health + 0x38;
            if (health < 0xff) {
                player->health = health;
            } else {
                player->health = 0xff;
            }
        }
        func_02085f98(player, 0x4a);
        break;
    case 8:
        if (player->objKind == 1) {
            AddRupee(player, 0x64);
        }
        break;
    case 9:
        if (player->objKind == 1) {
            AddRupee(player, 0xc8);
        }
        break;
    case 10:
        if (player->objKind == 1) {
            func_02085f98(player, 0x7a);
            if (POWERUP_LEVELS(p0)->power < 2) {
                Knife_Hud_HudManager_startPowerUpAnim((u8 *)app + 0x1f8, e0->type);
                if (e0 != e1) {
                    Knife_Hud_HudManager_startPowerUpAnim((u8 *)app + 0x1f8, e1->type);
                }
                POWERUP_LEVELS(p0)->power = POWERUP_LEVELS(p0)->power + 1;
                POWERUP_LEVELS(p1)->power = POWERUP_LEVELS(p0)->power;
            }
        }
        break;
    case 11:
        if (player->objKind == 1) {
            func_02085f98(player, 0x7a);
            if (POWERUP_LEVELS(p0)->defence < 2) {
                Knife_Hud_HudManager_startDefenceUpAnim((u8 *)app + 0x1f8, e0->type);
                if (e0 != e1) {
                    Knife_Hud_HudManager_startDefenceUpAnim((u8 *)app + 0x1f8, e1->type);
                }
                POWERUP_LEVELS(p0)->defence = POWERUP_LEVELS(p0)->defence + 1;
                POWERUP_LEVELS(p1)->defence = POWERUP_LEVELS(p0)->defence;
            }
        }
        break;
    case 12:
        if (player->objKind == 1) {
            func_02085f98(player, 0x7a);
            if (POWERUP_LEVELS(p0)->speed < 2) {
                Knife_Hud_HudManager_startSpeedUpAnim((u8 *)app + 0x1f8, e0->type);
                if (e0 != e1) {
                    Knife_Hud_HudManager_startSpeedUpAnim((u8 *)app + 0x1f8, e1->type);
                }
                POWERUP_LEVELS(p0)->speed = POWERUP_LEVELS(p0)->speed + 1;
                POWERUP_LEVELS(p1)->speed = POWERUP_LEVELS(p0)->speed;
            }
        }
        break;
    case 13:
        if (player->objKind == 1) {
            SoundReq(0x95);
            DropRupees(player->type, 0x50);
            setWork = GetSetWork(0xf, 0x18, 0x60);
            if (setWork != NULL) {
                ObjPosCopyOfs32(player, setWork, 0, -0xc0000);
                *(u32 *)((u8 *)setWork + 0x7c) = player->type | 0x80;
            }
        }
        break;
    }
}
