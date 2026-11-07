#ifndef WIP_E_RADAR_INIT_E_H
#define WIP_E_RADAR_INIT_E_H

#include "engine/functions.h"
#include "knife/subtask/subtask_init.h"
extern s32 OamRing_dmaNo; // DMA channel of the OAM fill (engine/oam_ring.h)
#include "game/radar_api.h"

// Radar status block (SUBTASK_RADAR_WORK, 0x68 bytes) as GetSubtaskRadarStatus fills it: the values the radar
// screen draws, then four slots that start at -1
typedef struct SubtaskRadarStatus {
    s32 stage;       // 0x00: index into the stage name table (difficulty 2 and up use entry 2)
    s32 area;        // 0x04
    s32 time;        // 0x08: seconds
    s32 power;       // 0x0c: power level of the player (two bits)
    s32 defense;     // 0x10
    s32 speed;       // 0x14
    s32 kakera;      // 0x18
    s32 player;      // 0x1c: index of the local player
    s32 slot[4];     // 0x20, -1 = unused; cleared when the player's call animation just started
    struct {
        s32 x;
        s32 y;
    } pos[4];        // 0x30: player positions on the radar (map coordinates / 7)
    s32 present[4];  // 0x50: 1 when the player is in the game
    s32 unk_60;      // 0x60: goal x (target / 7)
    s32 unk_64;      // 0x64: goal y
} SubtaskRadarStatus;

// Work block of the subtask screens at data_0217d348 as the radar screen uses it
typedef struct SubtaskRadarWork {
    u8 unk_000[0x51c];
    s32 phase;                 // 0x51c
    u8 unk_520[0x934 - 0x520];
    void *nrcsData;            // 0x934: data of the radar background (NRCS chunk of data 0x24)
} SubtaskRadarWork;

// The radar screen keeps its status inside the work block at +0xb4+0x400
typedef struct SubtaskRadarBlock {
    u8 unk_000[0x400];
    SubtaskRadarStatus status; // 0x400 (work + 0x4b4)
} SubtaskRadarBlock;

extern SubtaskRadarWork *data_0217d348;
// Slot block of the subtask background loader (data_0217a2f8): base and chunk object of slot c at 0x10 and 0x14
typedef struct RadarBgBlock {
    u8 unk_00[0x10];
    void *cBase;     // 0x10
    u8 *cObj;        // 0x14: NRCS chunk, size at 0x08, data at 0x0c
} RadarBgBlock;

extern u8 data_0217a2f8[];
extern u8 *data_0212c55c;

void subTaskSendScr(s16 index, void *data, u32 offset, u32 size);
s32 _get_subtask_data(s32 index);
s32 _get_subtask_data_size(s32 index);

extern "C" {
s32 KnifeApp_getCurrentLanguage(void *app);
void Knife_Message_SetupTextRenderer(void *sceneInfo, s32 language, void *textGetter);
void MI_CpuCopy8(const void *src, void *dst, u32 size);
void MI_CpuFill8(void *dst, u8 value, u32 size);
s32 ResChunk_GetNRCS(void *entry, void *owner);
void GetSubtaskRadarStatus(SubtaskRadarStatus *status);
void subtask_init_hblank_raster(s32 mode);
void MI_WaitDma(u32 dmaNo);
void draw_radar_stage(s32 mode, void *buf);
void draw_radar_area(s32 mode, void *buf);
void subTask_radar_init(void);
}

#endif
