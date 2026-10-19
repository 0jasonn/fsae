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


#include "game/pl.h"

#define PL_ARR (*(PlWork (*)[4])data_0212ceb0)

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



ARM void pause_retry(void) {
    if (data_0212c5ac.blendEnabled != 0) {
        return;
    }
    DispReset();
    *(u16 *)0x05000000 = 0;
    data_021355a0 = 0;
    ObjWorkPoolClear();
    ObjMoveInit();
    MessageInitialize();
    TelopInitialize();
    func_02029a50(pauseState, 0x20);
    *((u8 *)&data_0212c7c8 + 0x8c) = 1;
    data_0212c4b8 = 1;
    data_0212c520 = 1;
    data_0212c500 = 1;
    data_0212c4dc = 0;
}

ARM void keyDisable(void) {
    u8 i;
    u8 playerCount;

    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        return;
    }
    playerCount = data_0212c5bc[0x11] & 3;
    for (i = 0; i < 4; i++) {
        if (i != playerCount) {
            data_0212c58c[i] = 0;
        }
    }
}

ARM void Entity_DispatchByUnk09(Entity *e) {
    entityDispatchTable[e->objId](e);
}

ARM void LinkControl(Entity *e) {
    u16 savedA;
    u16 savedB;
    u8 mode;

    savedA = data_0212c514;
    savedB = data_0212c510;
    mode = data_0212c4e4;
    data_0212c534 = e;
    if (mode == 2 || mode == 10) {
        data_0212c514 = data_0212c584[e->type];
        data_0212c510 = data_0212c58c[e->type];
    }
    func_02086740(e);
    data_0212c514 = savedA;
    data_0212c510 = savedB;
}

ARM void Entity_InitSpriteColor(Entity *e) {
    u32 settings;

    settings = *(u32 *)&e->spriteSettings;
    *(u32 *)&e->spriteSettings = (settings & ~0x300) | 0x200;
    func_02085cf8(e);
    scrollArgs[0] = 0x100;
    scrollArgs[1] = 0x100;
    scrollArgs[2] = 0;
    func_02083000(scrollArgs, objAffineSet + (((*(u32 *)&e->spriteSettings) << 2) >> 27) * 0x20);
    func_02083000(scrollArgs, objAffineSetAlt + (((*(u32 *)&e->spriteSettings) << 2) >> 27) * 0x20);
}

ARM void KobitoDemo(Entity *e) {
    scrollArgs[0] = *(u32 *)&e->unk_6c[0xc];
    scrollArgs[1] = *(u32 *)&e->unk_6c[0x10];
    scrollArgs[2] = 0;
    func_02083000(scrollArgs, objAffineSet + (e->spriteSettings.b24 >> 1) * 0x20);
    func_02083000(scrollArgs, objAffineSetAlt + (e->spriteSettings.b24 >> 1) * 0x20);
}
