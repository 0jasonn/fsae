#include "engine/functions.h"
#include "engine/misc.h"
#include "game/scene.h"
#include "global.h"
#include "types.h"
#include "ui/stagesel.h"

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
//   stagesel_save_tutorial_update

// Counts down the tutorial save dialog and, when it ends, closes the dialog and starts the next phase
void stagesel_save_tutorial_update(void) {
    if ((s8)data_02171d58.unk_00[1] == 0) {
        return;
    }
    data_02171d58.unk_00[2] = (u8)((s8)data_02171d58.unk_00[2] - 1);
    if ((s8)data_02171d58.unk_00[2] != 0) {
        return;
    }
    stagesel_dialogDelete();
    SoundReq(0x80010000);
    SoundReq(0x3e);
    SoundReq(0x4d);
    data_0212c75c.reg66 = 0x3fff;
    ZeldaFadeFinish();
    ZeldaFadeSet(*(Entity **)&data_0212c648, 0);
    data_0212c500++;
    ComRequest(5);
}
