#ifndef WIP_C_C_DECLS_H_2
#define WIP_C_C_DECLS_H_2

// Declarations used by the wip C units that are not in engine/functions.h yet. Plain original names are C
// linkage (extern "C"), _Z names are C++ linkage. The reviewer moves these into functions.h when integrating.
#include "engine/functions.h"
#include "engine/player.h"

extern "C" {
void BgInit(void);
void func_020841b0(Entity *e);
void CheckInit(void);
void CheckPlsSet(void);
void CockpitInit(void);
void StaffrollLoad(void);
void initRupeeRush(void);
void setupTreasureBox(void);
u8 getRupeeRushDiceIndex(void);
u32 getNumberOfObj(u8 kind, u8 id);
void kabutoEvent(Entity *e);
void sword_plsync(Entity *e, Entity *other);
}

void ClearWorkBuffer(void);
void DispReset(void);
void LoadJyouchuu(void);
void PlWorkReset(void);
void RandomSetInit(void);
void ShikakeInit(void);
void ScrollMove(void);
void BgAnm(void);
void CommFrameSync(void);
void CommFrameUpdate(void);
void func_0208309c(void);
void Knife_Single_SinglePlay_Initialize(void);
void zFree(void *p);

// Data of the rupee rush and staffroll sequences (names are the dsd names unless renamed in scratch/agentC/renames.txt)
extern u8 data_0212c5ac[];
extern u16 data_021355a0;
extern u8 data_0212caf0[];
extern u32 data_0212c558;
extern u16 data_0212c540;
extern u8 frameCounter[];
extern u16 data_0212c75c[];
extern u8 data_0212c500;

#endif
