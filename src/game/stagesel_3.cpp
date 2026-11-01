#include "engine/functions.h"
#include "engine/misc_d.h"
#include "game/scene_d.h"
#include "global.h"
#include "types.h"
#include "game/stagesel.h"

// Shared object pointer table (data_02171d58); only the pointers used by the stage select code are named
typedef struct SselObjTable {
    /* 00 */ u8 unk_00[8];
    /* 08 */ Entity *unk_08;
    /* 0c */ Entity *unk_0c;
    /* 10 */ u8 unk_10[4];
    /* 14 */ Entity *pleaseWait;
    /* 18 */ u8 unk_18[4];
    /* 1c */ Entity *unk_1c;
} SselObjTable;

// Per-player flags entry (enemyTypeFlags, 8 bytes per player); the header that names it is not included here
typedef struct SselPlayerFlags {
    /* 00 */ u32 flags;
    /* 04 */ u8 unk_04[4];
} SselPlayerFlags;

extern SselDialogParams data_02116720;

extern const SselDialogRow data_020dc6bc[];
extern const u8 data_02116754[];

extern u16 data_021355a0;
extern u8 data_02171d7c[];
extern u8 data_0211678c[];

extern SselObjTable data_02171d58;
extern const VoidFunc data_02116728[];
extern u8 data_020dc668[];
extern Entity *data_02171e1c;

extern SselPlayerFlags enemyTypeFlags[];
extern u32 data_02134900;

// Functions in this file (original names from the debug build):
//   start_select, set_please_wait, del_please_wait

// Starts the stage select screen for mode: loads the character effect, creates the cursor work and the please wait
void start_select(int mode) {
    Entity *cursor;

    effect_char_load(*((u8 *)KnifeApp_getInstance() + 0xcb0), mode);
    GetSetWork(0x46, 6, *((u8 *)KnifeApp_getInstance() + 0xcb0));
    cursor = GetSetWork(0x46, 7, 0);
    *(Entity **)&data_0212c648 = cursor;
    data_02171d58.unk_08 = cursor;
    data_0212c4dc = 0;
    data_0212c500 = 4;
    if (localPlayerIndex != 0) {
        set_please_wait();
    } else {
        del_please_wait();
    }
}

// Shows the please wait message object (once) with the three waiting text sprites
void set_please_wait(void) {
    Entity *work;

    if (data_02171d58.pleaseWait != 0) {
        return;
    }
    work = GetSetWork(0x46, 5, 0);
    data_02171d58.pleaseWait = work;
    work->x.HALF.HI = 0x78;
    data_02171d58.pleaseWait->y.HALF.HI = 0x50;
    data_02171d58.pleaseWait->unk_1b = 0x4e;
    data_02171d58.pleaseWait->spriteSettings.b16 = 0;
}

// Removes the please wait message object, if one is shown
void del_please_wait(void) {
    if (data_02171d58.pleaseWait == 0) {
        return;
    }
    PutObjWork(data_02171d58.pleaseWait);
    data_02171d58.pleaseWait = 0;
}
