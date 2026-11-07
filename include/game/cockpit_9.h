#ifndef WIP_A_COCKPIT_9_H
#define WIP_A_COCKPIT_9_H

// Declarations used by src/wip/A/cockpit_9.cpp (cockpit module, map mode and HUD frame).
#include "engine/functions.h"
#include "engine/misc.h"

extern u8 data_0212c830[];   // per-player value copied to the HUD block byte 0x0a
extern u8 data_0212c4c8;     // local player index for the HUD

// HUD block at cockpitState (cockpitState[]): 0 active, 2 redraw request, 3 buffer index, 4 clear mask,
// 5 map mode step, 0x0a copy of data_0212c830[local player]
#define HUD_ACTIVE 0
#define HUD_REDRAW 2
#define HUD_BUFFER 3
#define HUD_CLEAR_MASK 4
#define HUD_MAP_STEP 5
#define HUD_LAST_VALUE 0x0a
#define RUPEE_S32(off) (*(s32 *)(cockpitState + (off)))

extern u8 pauseDialogWindow[];

extern "C" {
void fill_rect(u8 x, u8 y, u8 width, u8 height);   // 0x0202688c
void mapmode_move(void);                           // 0x02026a34
void CockpitInit(void);                            // 0x020264f4
void Cockpit(void);                                // 0x02026b98
void cockpit_move(void);
void cockpit_bg_trans(void);
void cockpit_obj_set(u8 index);
}
void CockpitUpdate(void);                          // 0x02026628, C++ (original CockpitUpdate())
void cockpit_obj_trans(u8 mode);
void cockpit_load(void);
void kakera_disp(void);
void kinomi_disp(void);
void MapMarkerSet(void);
void cockpit_write_rupee(u16 *dst, u32 value, u8 count, u16 flags);   // original write_rupee
extern "C" BOOL Knife_Message_selectionDialog_isModal(const void *a);

#endif
