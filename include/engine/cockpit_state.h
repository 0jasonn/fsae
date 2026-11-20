#ifndef ENGINE_COCKPIT_STATE_H
#define ENGINE_COCKPIT_STATE_H

#include "types.h"

// Cockpit (HUD) block (cockpitState, 0x30 bytes up to mapState). CockpitInit() clears all 0x30 bytes. The HUD tile map is
// double buffered in data_021361a0: bufferIndex selects the 0x800-byte page being drawn, Cockpit flips it each frame.
typedef struct CockpitState {
    /* 00 */ u8 mode;        // 0 off (CockpitOff, ending, opening), 1 HUD active (CockpitInit, cockpit_14), 2 set on a warp
    /* 01 */ u8 unk_01;      // cleared by CockpitOff
    /* 02 */ u8 redraw;      // nonzero requests a full redraw/transfer of the HUD page
    /* 03 */ u8 bufferIndex; // HUD page (0 or 1) in data_021361a0, 0x800 bytes each
    /* 04 */ u8 clearMask;   // pages still to be cleared (CockpitOff sets 3)
    /* 05 */ u8 mapStep;     // map mode step; nonzero also makes bg_trans_body draw kakera and kinomi
    /* 06 */ u8 unk_06;
    /* 07 */ u8 kattiKind;   // katti graphics kind loaded at 0x06014200 (0xff none)
    /* 08 */ u8 hearts;      // displayed health, moved one step per update towards the player's health
    /* 09 */ u8 heartKind;   // argument of heartUpdate
    /* 0a */ u8 kakeraCount; // copy of gameState.kakeraCount[local player] (kakera count)
    /* 0b */ u8 transMask;   // bitmask of pages already transferred by cockpit_bg_trans
    /* 0c */ u8 item;        // first player's item index (0 none, 0xff unset)
    /* 0d */ u8 unk_0d;      // copy of gameState.unk_24 & 0x7f, a change requests a redraw
    /* 0e */ u8 itemState;   // item 7 uses colour 4 when this is 2
    /* 0f */ u8 unk_0f;
    /* 10 */ s32 rupees;     // displayed rupee count, moved towards gameState.score by rupeeUpdate
    /* 14 */ s32 rupeeShown;      // rupee change shown in the HUD (0 none)
    /* 18 */ s32 rupeeGain;       // AddRupee: sum of gains, max 9999, shown for 0x78 frames
    /* 1c */ s32 rupeeLoss;       // AddRupee: sum of losses, min -9999, shown for 0x3c frames
    /* 20 */ u16 rupeeGainTimer;
    /* 22 */ u16 rupeeLossTimer;
    /* 24 */ u16 kakeraTimer[4]; // per-player kakera timers (also the dsd symbol data_0212c63c)
    /* 2c */ u8 item2p;      // second player's item index
    /* 2d */ u8 itemState2p; // same as itemState for item2p
    /* 2e */ u8 unk_2e[2];
} CockpitState;
extern CockpitState cockpitState; // 0x0212c618

// HUD/message BG tile map (0x1000 bytes): two 0x800-byte pages (32x32 u16 entries), page cockpitState.bufferIndex is
// the one being drawn. The message windows draw into the same pages. (dsd's data_021369a0 is page 1.)
extern u8 data_021361a0[2][0x800];

#endif
