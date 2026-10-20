#include "engine/functions.h"
#include "global.h"
#include "object/tama11.h"

// yousei module (fairy demo), 0x02081b64 onward.
//   YouseiDemoTask (0x02081ba4): runs the current demo step (table yousei_demoTable), then the frame's shared update.

extern u8 data_0212c500;      // current demo step
extern u32 data_0212c564;     // callback run after each step
extern u16 data_0212c75c;     // display flags; bit 11 is cleared each frame
extern void (*const yousei_demoTable[])(void);
BOOL CommFrameSync(void);
void CommUpdateJoy(void);
void ScrollMove(void);
void BgAnm(void);
void CommFrameUpdate(void);
void func_0208309c(void);
extern s16 demolinkPosTable[];
s16 *GetTablePlNum(s16 *table, u8 index);
extern u32 data_0212c648;

extern "C" int func_02081b64(void);

// func_02081b64 (0x02081b64): true when every player in the game state has bit 9 set in its status word.
// Unmangled: implementer D's set58 calls it through extern "C".
ARM int func_02081b64(void) {
    s32 i;
    s32 count;

    count = data_0212c7c8.unk_0;
    for (i = 0; i < count; i++) {
        if ((*(u32 *)((u8 *)&data_0212c7c8 + i * 8 + 0x28) & 0x200) == 0) {
            return 0;
        }
    }
    return 1;
}

// YouseiDemoTask (0x02081ba4)
ARM void YouseiDemoTask(void) {
    switch (data_0212c500) {
    case 0:
    case 4:
        yousei_demoTable[data_0212c500]();
        break;
    case 1:
    case 2:
    case 3:
        if (CommFrameSync() != 0) {
            CommUpdateJoy();
            yousei_demoTable[data_0212c500]();
            ((void (*)(void))data_0212c564)();
            ScrollMove();
            BgAnm();
            func_0208309c();
            VGroupManager();
            func_020830ec();
            CommFrameUpdate();
        }
        break;
    }
    data_0212c75c &= 0xf7ff;
}

// demolink_set (0x02081c50): places each player's demo object at its table position and sets the player's demo state.
ARM void demolink_set(void) {
    u8 i;
    s16 *pos;
    Entity *e;

    pos = GetTablePlNum(demolinkPosTable, 0);
    i = 0;
    while (i < data_0212c7c8.unk_0) {
        e = func_02072554(i);
        e->x.HALF.HI = pos[0];
        e->y.HALF.HI = 0x178;
        e->spriteSettings.b0 = 1;
        e->spriteSettings.b30 = 1;
        e->animationState = 0;
        e->spriteSettings.b14 = 2;
        e->unk_2e = 3;
        e->unk_5e.b2 = 1;
        data_0212ceb0[i].state = 2;
        data_0212ceb0[i].stateTimer = pos[1];
        data_0212ceb0[i].unk_39 = pos[1] >> 8;
        i++;
        pos += 2;
    }
    data_0212c648 = (u32)GetSetWork(0xd, 0xb, 0);
}
