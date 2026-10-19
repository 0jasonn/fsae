#include "engine/entity.h"
#include "global.h"

// Functions in this file (address -> name, pending reviewer apply to symbols.txt):
//   SceneState_Start -> SceneState_Start
//   SceneState_WaitHigh -> SceneState_WaitHigh
//   SceneState_Fade -> SceneState_Fade
//   SceneState_WaitLow -> SceneState_WaitLow

// Work blocks in the bss, accessed by byte offset
extern u8 data_0217d39c[];
extern u8 data_0217d484[];

extern void SoundReq(int sfx);
extern void SceneState_SetMode(int mode);
extern int func_0204ab20(int mode);
extern int SceneState_Adjust(int mode);

// Scene state handlers: a table entry returns 0 when the state is done
ARM int SceneState_Start(void) {
    if (data_0217d39c[0xe3] != 1) {
        data_0217d39c[0xe3] = 1;
        SoundReq(0x43);
    }
    SceneState_SetMode(2);
    if (func_0204ab20(1) != 0) {
        data_0217d39c[0xd0] = 3;
    }
    return 0;
}

ARM int SceneState_WaitHigh(void) {
    if (SceneState_Adjust(-1) != 0) {
        data_0217d484[0xd0] = 3;
    }
    return 0;
}

ARM int SceneState_Fade(void) {
    if (data_0217d39c[0xe3] != 3) {
        data_0217d39c[0xe3] = 3;
        data_0217d39c[0xaf] = 0;
        data_0217d39c[0xae] = 0;
        data_0217d39c[0xad] = 0;
        data_0217d39c[0xac] = 0;
        SoundReq(0x44);
    }
    SceneState_SetMode(7);
    if (func_0204ab20(-1) != 0) {
        data_0217d39c[0xd0] = 5;
    }
    return 0;
}

ARM int SceneState_WaitLow(void) {
    if (SceneState_Adjust(1) != 0) {
        data_0217d484[0xd0] = 5;
    }
    return 0;
}
