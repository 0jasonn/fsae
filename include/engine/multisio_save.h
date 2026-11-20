#ifndef ENGINE_MULTISIO_SAVE_H
#define ENGINE_MULTISIO_SAVE_H

#include "types.h"

// Save slot (data_021350b0, 3 slots of 0x50 bytes): the file entry that the fs* functions read and clear, and the send
// table entry selected by multiSioSelect.index. Sub-symbols: data_021350b4..b6 (+0x04..+0x06), data_021350b8 (str08),
// data_021350c8 (w18), data_021350dc/dd (unk_2c/unk_2d), data_021350f7 (status), data_021350f8 (b48).
typedef struct MultiSioEntry {
    /* 00 */ u32 word00;
    /* 04 */ union {
        u32 word04;          // read and written as one word
        struct {
            /* 04 */ u8 unk_04;
            /* 05 */ u8 b05;
            /* 06 */ u16 h06;
        };
    };
    /* 08 */ u16 str08[8];   // player name, zero-terminated (empty: no file); 0x34 bytes from here are sent
    /* 18 */ u32 w18;
    /* 1c */ u8 unk_1c[0x2c - 0x1c];
    /* 2c */ u8 unk_2c;      // set to 1 by clearSaveData and fsCreateFile
    /* 2d */ u8 unk_2d;      // set to 1 by clearSaveData and fsCreateFile
    /* 2e */ u8 unk_2e[0x47 - 0x2e];
    /* 47 */ s8 status;      // file status from Knife_readMediaFlagged (0: ok, 3/4/6/8: errors, 7: copied)
    /* 48 */ u8 b48;
    /* 49 */ u8 unk_49[0x50 - 0x49];
} MultiSioEntry;
extern MultiSioEntry data_021350b0[3];

// System save block (multiSioSelect, 0x10 bytes): the slot 7 area that Knife_WriteToMedia writes before every slot.
// index selects the entry of the send table data_021350b0 (and the name plate shown for the local player).
typedef struct MultiSioSelect {
    /* 00 */ u8 unk_00[4];
    /* 04 */ u8 index;
    /* 05 */ u8 unk_05[0x10 - 0x05];
} MultiSioSelect;
extern MultiSioSelect multiSioSelect;

#endif
