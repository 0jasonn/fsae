#include "engine/functions.h"
#include "engine/misc_d.h"
#include "game/scene_d.h"
#include "global.h"
#include "types.h"
#include "game/stagesel.h"


// Parameter block of the stage select message dialog (data_02116720). Only the fields used here are named.
typedef struct SselDialogParams {
    /* 00 */ u8 unk_00[0x34];
    /* 34 */ u32 bgVramBase; // 0x06000000
    /* 38 */ u8 unk_38[0xc];
    /* 44 */ u16 unk_44;
    /* 46 */ u8 unk_46[0x22];
    /* 68 */ void *msgScrn; // KnifeApp work + 0x1bc
    /* 6c */ void *dialogBuffer;
    /* 70 */ u8 unk_70[8];
    /* 78 */ u32 unk_78;
    /* 7c */ u16 unk_7c;
    /* 7e */ u8 unk_7e;
    /* 7f */ u8 unk_7f[0x21];
    /* a0 */ void *msgScrnPause;
} SselDialogParams;
extern SselDialogParams data_02116720;

// One 6-byte row of the stage select dialog table: layout key, message index and sound effect
typedef struct SselDialogRow {
    u16 layout;
    u16 msgIndex;
    u16 sfxId;
} SselDialogRow;
extern const SselDialogRow data_020dc6bc[];
extern const u8 data_02116754[];

extern u16 data_021355a0;
extern u8 data_02171d7c[];
extern u8 data_0211678c[];

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
extern SselObjTable data_02171d58;
extern const VoidFunc data_02116728[];
extern u8 data_020dc668[];
extern Entity *data_02171e1c;

// Per-player flags entry (enemyTypeFlags, 8 bytes per player); the header that names it is not included here
typedef struct SselPlayerFlags {
    /* 00 */ u32 flags;
    /* 04 */ u8 unk_04[4];
} SselPlayerFlags;
extern SselPlayerFlags enemyTypeFlags[];
extern u32 data_02134900;

// Functions in this file (original names from the debug build):
//   sr_exit

// Leaves the stage select screen once no blend fade is running: resets the display and the object work pool
ARM void sr_exit(void) {
    if (data_0212c5ac.blendEnabled != 0) {
        return;
    }
    DispReset();
    *(u16 *)0x05000000 = 0;
    data_021355a0 = 0;
    ObjWorkPoolClear();
    ObjMoveInit();
    EndingFinish();
}
