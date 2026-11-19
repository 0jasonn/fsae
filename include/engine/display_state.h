#ifndef ENGINE_DISPLAY_STATE_H
#define ENGINE_DISPLAY_STATE_H

#include "types.h"

// One BG entry of the display shadow (0xc bytes). ResourceCtrl calls bgTrans(&entry) when transRequest and buffer
// are both set.
typedef struct DispBg {
    /* 00 */ u16 cnt;          // BGxCNT value (initial values from the BG table at data_020ce4d0 + 0x20..0x26)
    /* 02 */ u16 scrollX;      // BGxHOFS
    /* 04 */ u16 scrollY;      // BGxVOFS
    /* 06 */ u16 transRequest; // nonzero: transfer buffer in VBlank
    /* 08 */ void *buffer;     // source of the transfer (e.g. a page of data_021361a0)
} DispBg;

// Display shadow (displayState, 0x6c bytes): display control flags and BG/window/blend register mirrors that are copied
// to the hardware in VBlank. DispCtrlClear() clears all 0x6c bytes and sets displayFlags to 0x40. data_0212c6f0, the
// block just before it, has the same layout and is passed to the ResourceCtrl callback as a DISP_CTRL_ *, so the
// original tag is taken to be DISP_CTRL_.
typedef struct DISP_CTRL_ {
    /* 00 */ u16 displayFlags; // DISPCNT mirror: bits 8-12 BG0-3/OBJ on, 13-14 windows 0/1; bit 11 cleared each frame by yousei
    /* 02 */ u8 unk_02[2];
    /* 04 */ u16 savedFlags; // copy of displayFlags (written by makemap_30, restored by multiplay_startdemo)
    /* 06 */ u8 unk_06[2];
    /* 08 */ DispBg bg[4];
    /* 38 */ u8 unk_38[0x20];
    /* 58 */ u16 win0H;      // WIN0H; also the first span word of the HBlank window table (circle/triangle windows)
    /* 5a */ u16 win1H;      // WIN1H (guess)
    /* 5c */ u16 win0V;      // WIN0V
    /* 5e */ u16 win1V;      // WIN1V (guess)
    /* 60 */ u16 winIn;      // WININ
    /* 62 */ u16 winOut;     // WINOUT
    /* 64 */ u16 unk_64;     // MOSAIC slot (guess)
    /* 66 */ u16 blendCnt;   // BLDCNT
    /* 68 */ u16 blendAlpha; // BLDALPHA (EVA | EVB << 8)
    /* 6a */ u16 blendY;     // BLDY, 0..0x10 (brightness fade)
} DISP_CTRL_;
typedef DISP_CTRL_ DisplayState;

extern DisplayState displayState; // 0x0212c75c
// Second display block (0x0212c6f0, 0x6c bytes up to displayState): ResourceCtrl passes it to the resource callback
// (title_resourceCtrlCallback), transfers its BG entries with bgTrans and uses displayFlags bit 12 for the OBJ
// affine upload. dsd's data_0212c6f8/704/710/71c are its bg[0..3].
extern DisplayState data_0212c6f0;
// Pointer to the display block that DispCtrlClear clears (0x0212c568); set58 (hane_init) writes its blend registers.
extern DisplayState *data_0212c568;

#endif
