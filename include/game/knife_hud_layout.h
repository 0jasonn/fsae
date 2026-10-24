#ifndef WIP_E_KNIFE_HUD_LAYOUT_H
#define WIP_E_KNIFE_HUD_LAYOUT_H

#include "types.h"
#include "game/knife_interp.h"
#include "game/knife_hud.h"

// Full layout of Knife::Hud::HudManager, for the functions that reach fields game/knife_hud.h does not name yet.
// Used through a cast of `this`; game/knife_hud.h keeps the class definition.

// Interpolation of VecFx32 (Knife::Interp<VecFx32>, 0x30 bytes): vtable (data_0211c6f8), start a, end b, current value,
// time t (0x1000 = 1.0) and the interpolation function fn (NULL: no function, the value is b at t >= 1.0, else a)
typedef struct KnifeHudInterp {
    void *vtbl;      // 0x00
    VecFx32 a;       // 0x04
    VecFx32 b;       // 0x10
    VecFx32 value;   // 0x1c
    s32 t;           // 0x28
    void *fn;        // 0x2c
} KnifeHudInterp;

// Status-up marker (0x38 bytes, four at +0x80): two words, then an interpolation at +0x08
typedef struct KnifeHudStatusUpMarker {
    s32 unk_00;
    s32 unk_04;
    KnifeHudInterp interp; // 0x08
} KnifeHudStatusUpMarker;

// Entry of the 16-entry record table at +0x178 (0x14 bytes)
typedef struct KnifeHudRecord {
    s32 unk_00; // 0xff ... set to -1 by finalize
    s32 unk_04;
    s32 unk_08;
    s32 unk_0c;
    s32 unk_10;
} KnifeHudRecord;

// HudManager with every field the functions of knife_hud_7.cpp and knife_hud_8.cpp use
typedef struct KnifeHudVars {
    void *vtbl;                              // 0x00
    u8 initialized;                          // 0x04
    u8 unk_05[3];
    s32 activePlayer;                        // 0x08: 0xff while no player is active
    KnifeHudInterp interp[2];                // 0x0c: two interpolations (0x30 each)
    s32 field6c;                             // 0x6c: 0x199 after finalize
    s32 field70[4];                          // 0x70: one value per player (0xff after finalize)
    KnifeHudStatusUpMarker statusUp[4];      // 0x80
    s32 callAnim[4];                         // 0x160
    s32 state170;                            // 0x170
    s32 unk_174;
    KnifeHudRecord records[16];              // 0x178
} KnifeHudVars;

// Initial values of the two interpolations, copied from the ROM by finalize (two VecFx32)
typedef struct KnifeHudInterpInit {
    VecFx32 first;
    VecFx32 second;
} KnifeHudInterpInit;

extern const KnifeHudInterpInit data_020ddd44;
extern char data_0211c6e8[]; // HudManager vtable
extern char data_0211c6f8[]; // Interp<VecFx32> vtable

void func_0200c7b8(void *array, s32 count, u32 size, void *ctor, void *dtor); // array constructor helper
extern "C" void func_0200c868(void *array, s32 count, u32 size, void *dtor);            // array destructor helper
extern u8 data_0212c618[];                                                    // cockpit block, byte 0 gates the HUD update
extern u8 objAffineSet[];                                                     // OAM buffer, 0x400 bytes per mode

// Members of HudManager that are not declared in game/knife_hud.h yet (C linkage, the object is the first argument)
extern "C" void Knife_Hud_HudManager_updateEquipIcon(Knife::Hud::HudManager *self, s32 mode);
extern "C" void Knife_Hud_HudManager_updateStatusUp(Knife::Hud::HudManager *self, s32 mode);
extern "C" void Knife_Hud_HudManager_updateCall(Knife::Hud::HudManager *self, s32 mode);
extern "C" void Knife_Hud_HudManager_updateGameOver(Knife::Hud::HudManager *self, s32 mode);

// One OAM entry as the HUD writes it: attr0 and attr1 together as one word, then attr2
typedef struct KnifeHudOamEntry {
    u32 attr01;
    u16 attr2;
    u16 unk_06;
} KnifeHudOamEntry;

// Function type of an interpolation (Knife::Interp<VecFx32>::fn): the result is returned through a pointer
typedef VecFx32 (*KnifeHudInterpFn)(const VecFx32 *a, const VecFx32 *b, s32 t);

#endif
