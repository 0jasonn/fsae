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

ARM void PlWorkReset(void) {
    PlWork *end;
    PlWork *p;

    p = PL_ARR;
    end = (PlWork *)&data_0212ceb0[4];
    if (p < end) {
        do {
            *((u8 *)&data_0212c594 + 4) = 0;
            p->unk_00 = 0;
            p->unk_01 = 0;
            p->unk_02 = 0;
            p->unk_03 = 0;
            p->unk_04 = 0;
            p->state = 0;
            p->unk_06 = 0;
            p->unk_07 = 0;
            p->unk_08 = 0;
            p->unk_0a = 0;
            p->unk_0b = 0;
            p->unk_0c = 0;
            p->unk_0d = 0;
            p->unk_0e = 0;
            p->unk_0f = 0;
            p->unk_10 = 0;
            p->unk_11 = 0;
            p->unk_12 = 0;
            p->unk_13 = 0;
            p->unk_14 = 0;
            p->unk_1b = 0;
            p->unk_1e = 0;
            p->unk_1f = 0;
            p->unk_20 = 0;
            p->unk_21 = 0;
            p->unk_22 = 0;
            p->unk_24 = 0;
            p->unk_34 = 0;
            p->unk_35 = 0;
            p->unk_36 = 0;
            p->unk_38 = 0;
            p->unk_39 = 0;
            p->unk_3a = 0;
            p->unk_3c = 0;
            p->unk_3d = 0;
            p->unk_26 = 0;
            p->yOffset = 0;
            p->unk_3e = (s32)p->unk_3e & ~0xc0;
            p->weapon = 0;
            p->unk_8b = (u8)(p->unk_8b & ~3) & ~0x70;
            OSi_CpuClear32(0xffffffff, p->unk_40, 0x40);
            p++;
        } while (p < end);
    }
    OSi_CpuClear32(0, data_0212c868, 0x140);
}
