#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"
#include "game/menu_wip.h"

// Functions in this file (provisional names, role not confirmed):
//   Menu_InitPool (Menu_InitPool)

extern "C" {
s32 func_020c0874(s32 value);
s32 func_020c0844(void);
void func_020c050c(void *obj, s32 value);
void func_020c1660(s32 value);
void SndSys_Init(void *obj);
void Menu_ClearRef(void *obj);
void SndSlot_ReleaseFirst(void *obj, s32 value);
void SndSys_Shutdown(void);
}

// Menu_InitPool (0x020bec80): sets up the pool object: the entries (id -1), the extra object at +0x234, the counts
// and the ready flag.
extern "C" void Menu_InitPool(MenuPool *pool, s32 value);
ARM void Menu_InitPool(MenuPool *pool, s32 value) {
    u32 i;

    SndSys_Init(pool);
    func_020c050c(&pool->unk_10, value);
    func_020c1660(0);
    for (i = 0; i < 16; i++) {
        Menu_ClearRef(&pool->entries[i]);
        pool->entries[i].id = -1;
        pool->entries[i].unk_08 = 0;
        pool->entries[i].unk_0c = 0;
    }
    Menu_ClearRef(&pool->unk_234);
    *(s32 *)((u8 *)pool + 0x238) = -1;
    *(s32 *)((u8 *)pool + 0x23c) = 0;
    pool->current = 0;
    pool->count = func_020c0874(0);
    pool->unk_0c = func_020c0844();
    pool->ready = 1;
}
