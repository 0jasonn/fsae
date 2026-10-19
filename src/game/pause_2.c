#include "global.h"
#include "engine/misc_d.h"

// data_02134980 is the pause state block: [0] phase, [1] chosen pause option, [2] delay timer,
// [0xe] reset flag, [0xf] set when the wireless session is being closed

extern u8 data_02134980[];
extern u16 data_021355a0;
extern u16 data_0212c58c[];
extern u8 data_0212c4b8;
extern u8 data_0212c4d4;
extern u16 data_0212c520;

void keyDisable(void);
void pause_dialogUpdate(void);
void Task_Chain(s32 a);
void ObjMoveInit(void);
void MessageInitialize(void);
void SoundReq(u32 a);
void func_02029a50(void *dst, u32 size);
void func_0204bb9c(void);
s32 KnifeApp_isWirelessMode(void *a);
s32 CommJoyCheck(u16 keys);
void TelopInitialize(void);
void UnlockTokiWave(void);
void subTask_game_start_reload(void);
void func_02028024(void);
void func_020827a8(s32 a);
void eff_fade_out_init(s32 a);
void eff_white_out_init(s32 a);
void *func_020909c8(void);
s32 func_02090ecc(void *manager);
s32 Knife_Comm_WirelessManager_getState(void *manager);
void Knife_Comm_WirelessManager_turnOff(void *manager);

#include "game/pl.h"

#define PL_ARR (*(PlWork (*)[4])data_0212ceb0)

extern u16 data_0212c574[];
extern u8 data_0212dd90[];
extern u8 data_0212e190[];
extern u8 data_0212c4e4;
extern u16 data_0212c514;
extern u16 data_0212c510;
extern Entity *data_0212c534;
extern u16 data_0212c584[];
extern u8 data_0212c868[];
extern const EntityFunc data_02115258[];

void func_02085cf8(Entity *e);
void func_02086740(Entity *e);
void func_0208919c(Entity *e);
void func_02083000(void *dst, const void *src);
void OSi_CpuClear32(u32 value, void *dst, u32 size);

Entity *GetObjWork(void);
void RegistObjWork(int list, Entity *e);
void TelopRequest(u16 telop);
void func_0208ab14(Entity *a, Entity *b);
void func_0208a95c(Entity *e);
void PlLiftSync(Entity *e);
void PlWeaponSync(Entity *e, Entity *weapon);
extern u8 data_0217d36c[];
extern const u32 data_021186e4[];
extern const u8 data_0212c84c[];

extern const s8 *const data_0211525c[];
void ObjLiftPrioCheck(Entity *e);

extern const VoidFunc data_02115268[];
extern u8 data_0212c504;

Entity *func_02072554(s32 a);
void DemoLinkWalkSet(s32 a, s32 b, s32 c);
Entity *GetSetWork(s32 a, s32 b, s32 c);

void BindPlayer(u8 playerNo);

ARM void pause_wait(void) {
    keyDisable();
    if ((data_0212c5bc[0x11] & 3) == data_0212c504) {
        pause_dialogUpdate();
    }
    if (--data_02134980[2] == 0) {
        data_02134980[0]++;
    }
}
