#include "engine/functions.h"
#include "global.h"
#include "game/hitdecls.h"

// Bomb main (module bomb, second unit). Named Bomb (Bomb renamed in scratch/agentE/renames.txt).

typedef struct Vars_Bomb {
    u8 unk_00[0x60];
    s32 flashPhase; // 0x60: phase of the flash (bombFlash), moved by 0x10 per frame and toggled at the end of a cycle
    u16 fireTimer; // 0x64: non-zero while the bomb is being set off (bombFire runs instead of the state handler)
} Vars_Bomb;

extern const EntityFunc data_020ce50c[]; // state handlers, indexed by e->action
extern const u8 data_020ce4fc[]; // hitbox of the bomb after it was set off
extern u8 data_0212ceb5[]; // one byte per template entry (0x94 apart), cleared when a carried bomb is dropped
extern u8 data_0212c4b8; // non-zero while the object update is frozen
extern KnifeObjAffineSrcData scrollArgs;
extern const u8 bomb_hitbox[]; // hitbox of a bomb (bomb_hitbox) // affine source for the flash: scale 0x100, 0x100, angle 0

// Bomb main: runs the state handler while the game is not frozen (or the bomb is idle), and the flash and fuse
// timers, then the common object update.
ARM void Bomb(Entity *e) {
    Entity *child;

    if (data_0212c4b8 == 0 || e->action == 0) {
        if (VARS(Vars_Bomb, e)->fireTimer != 0) {
            bombFire(e);
        } else {
            data_020ce50c[e->action](e);
            UpdateAnimationSingleFrame(e);
            if (e->action != 3) {
                if (e->timer != 0) {
                    e->timer--;
                    if (e->timer == 0) {
                        e->subtimer = 0x50;
                        e->linkedEntity = NULL;
                        *(u32 *)&e->spriteSettings = (*(u32 *)&e->spriteSettings & ~0x300) | 0x200;
                        func_02085cf8(e);
                        scrollArgs.data[0] = 0x100;
                        scrollArgs.data[1] = 0x100;
                        scrollArgs.data[2] = 0;
                        ObjAffineSet2(&scrollArgs, e);
                    }
                } else {
                    if (e->subtimer != 0) {
                        e->subtimer--;
                        if (e->subtimer == 0) {
                            if (e->action == 2 && e->subAction == 1) {
                                *(u8 *)(data_0212ceb5 + e->type2 * 0x94) = 0;
                            }
                            func_02085d34(e);
                            e->action = 3;
                            e->hitbox = data_020ce4fc;
                            e->unk_2e = 0;
                            e->timer = 0xf;
                            e->spriteSettings.b0 = 0;
                            child = GetObjWork();
                            if (child != NULL) {
                                child->objId = 0x20;
                                child->objKind = 6;
                                child->type = e->type;
                                child->x.WORD = e->x.WORD;
                                child->y.WORD = e->y.WORD;
                                child->z.WORD = e->z.WORD;
                                child->layer = e->layer;
                                child->spriteSettings.b30 = e->spriteSettings.b30;
                                RegistObjWork(6, child);
                            }
                            TaimatuIgnition(e, 3);
                            BombWallCk(e);
                        } else {
                            bombFlash(e);
                        }
                    }
                }
            }
        }
    }
    func_020857c8(e);
}
