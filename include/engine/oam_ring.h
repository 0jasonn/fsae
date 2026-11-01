#ifndef WIP_G_OAM_RING_H
#define WIP_G_OAM_RING_H

#include "types.h"

// OAM allocation record (0x18 bytes). OamRing_Alloc fills it for one bank; the OBJ slots and affine groups it owns
// are the range start..end and affineStart..affineEnd.
typedef struct OamRing {
    /* 00 */ u32 bank;         // 0 main engine, 1 sub engine: picks the block below and the copy function
    /* 04 */ u16 start;        // first OBJ slot of the range
    /* 06 */ u16 end;          // last OBJ slot of the range (inclusive)
    /* 08 */ u16 cur;          // next OBJ slot that OamRing_Push writes
    /* 0a */ u16 affineStart;  // first affine group of the range
    /* 0c */ u16 affineEnd;    // last affine group (inclusive)
    /* 0e */ u16 affineCur;    // next affine group
    /* 10 */ u16 id;           // owner id written into the tag tables (taken from OamRing_idCounter)
    /* 12 */ u16 unk_12;
    /* 14 */ u32 active;       // nonzero: OamRing_Flush loads the range with GX(S)_LoadOAM instead of copying
} OamRing;

// One 8-byte OAM record as the pusher passes it: attribute 0, 1 and 2 (the rest is not copied).
typedef struct OamRecord {
    u16 attr0;
    u16 attr1;
    u16 attr2;
    u16 unk_6;
} OamRecord;

// Each OAM bank is a 0x540-byte block at OamRing_banks + bank * 0x540 (block 0 is OamRing_banks):
//   +0x000 u16 tags[0x80], owner id per OBJ slot, 0xffff when free
//   +0x100 attribute staging, 8 bytes per OBJ slot (affine groups of 0x20 bytes share this area)
//   +0x500 u16 affineTags[0x20], owner id per affine group, 0xffff when free
extern u8 OamRing_banks[];  // bank 0 block
extern u8 OamRing_attrs0[];  // bank 0 attributes
extern u8 OamRing_affineTags0[];  // bank 0 affine tags
extern u8 OamRing_banks1[];  // bank 1 block (tags)
extern u8 OamRing_attrs1[];  // bank 1 attributes
extern u8 OamRing_affineTags1[];  // bank 1 affine tags
extern u8 OamRing_banks2[];  // bank 2 block (tags)
extern u8 OamRing_attrs2[];  // bank 2 attributes
extern u8 OamRing_affineTags2[];  // bank 2 affine tags
extern u16 OamRing_idCounter;   // owner id counter, one per OamRing_Alloc
extern s32 OamRing_dmaNo;   // DMA channel for the OAM fill (0..3), -1 or above 3 means CPU fill
extern void (*OamRing_copyFuncs[2])(const void *src, u32 dst, u32 size); // VramObj_Copy16, VramObj_Copy16Offset

extern "C" {
void DC_FlushRange(void *base, u32 size);
void DC_InvalidateRange(void *base, u32 size);
void GX_LoadOAM(const void *src, u32 offset, u32 size);
void GXS_LoadOAM(const void *src, u32 offset, u32 size);
void MIi_DmaFill32(u32 dmaNo, void *dst, u32 value, u32 size, s32 flag);

void OamRing_ResetAll(void *oam);
s32 OamRing_Alloc(OamRing *ring, u32 start, u32 count, u32 bank);
s32 OamRing_Push(OamRing *ring, const OamRecord *records, s32 count);
void OamRing_Flush(OamRing *ring);
void OamRing_Clear(OamRing *ring);
}

#endif
