#ifndef WIP_B_FADE_NATIVE_H
#define WIP_B_FADE_NATIVE_H

// Declarations for the fade_native and write_native_init units of implementer B (0x020465ec to 0x02047454).

#include "engine/functions.h"

// RandomBlockSet lists (rodata, 0xff-separated entries) read by the native init routines.
extern const u8 nativeInitList_42e4[];
extern const u8 nativeInitList_42e7[];
extern const u8 nativeInitList_42ea[];
extern const u8 nativeInitList_42f1[];
extern const u8 nativeInitList_42f8[];
extern const u8 nativeInitList_42ff[];
extern const u8 nativeInitList_4306[];
extern const u8 nativeInitList_430d[];
extern const u8 nativeInitList_4314[];
extern const u8 nativeInitList_431c[];
extern const u8 nativeInitList_431f[];
extern const u8 nativeInitList_4322[];
extern const u8 nativeInitList_4325[];
extern const u8 nativeInitList_4328[];
extern const u8 nativeInitList_432f[];
extern const u8 nativeInitList_4338[];
extern const u8 nativeInitList_433b[];
extern const u8 nativeInitList_433e[];
extern const u8 nativeInitList_4341[];
extern const u8 nativeInitList_4344[];
extern const u8 nativeInitList_4348[];
extern const u8 nativeInitList_434b[];
extern const u8 nativeInitList_434e[];
extern const u8 nativeInitList_4351[];
extern const u8 nativeInitList_4354[];
extern const u8 nativeInitList_435d[];
extern const u8 nativeInitList_4366[];
extern const u8 nativeInitList_436f[];
extern const u8 nativeInitList_437c[];
extern const u8 nativeInitList_4389[];
extern const u8 nativeInitList_4396[];
extern const u8 nativeInitList_43a3[];
extern const u8 nativeInitList_43b0[];
extern const u8 nativeInitList_43bd[];
extern const u8 nativeInitList_43ca[];
extern const u8 nativeInitList_43d7[];
extern const u8 nativeInitList_43e4[];
extern const u8 nativeInitList_43e7[];
extern const u8 nativeInitList_43ea[];
extern const u8 nativeInitList_43ed[];
extern const u8 nativeInitList_43f0[];
extern const u8 nativeInitList_43f3[];
extern const u8 nativeInitList_43f6[];
extern const u8 nativeInitList_43f9[];
extern const u8 nativeInitList_43fc[];
extern const u8 nativeInitList_43ff[];
extern const u8 nativeInitList_4402[];
extern const u8 nativeInitList_4405[];
extern const u8 nativeInitList_4408[];
extern const u8 nativeInitList_440b[];
extern const u8 nativeInitList_440e[];
extern const u8 nativeInitList_4411[];
extern const u8 nativeInitList_4414[];
extern const u8 nativeInitList_4418[];
extern const u8 nativeInitList_4421[];
extern const u8 nativeInitList_442a[];
extern const u8 nativeInitList_4435[];
extern const u8 nativeInitList_4440[];
extern const u8 nativeInitList_4447[];
extern const u8 nativeInitList_444e[];
extern const u8 nativeInitList_4458[];
extern const u8 nativeInitList_445d[];
extern const u8 nativeInitList_4462[];
extern const u8 nativeInitList_4467[];
extern const u8 nativeInitList_446c[];
extern const u8 nativeInitList_6f52[];
extern const u8 nativeInitList_6f57[];
extern const u8 nativeInitList_6f5c[];
extern const u8 nativeInitList_932e[];
extern const u8 nativeInitList_9340[];
extern const u8 nativeInitList_9349[];
extern const u8 nativeInitList_9352[];
extern const u8 nativeInitList_935b[];
extern const u8 nativeInitList_9364[];
extern const u8 nativeInitList_b694[];
extern const u8 nativeInitList_b699[];
extern const u8 nativeInitList_b69e[];
extern const u8 nativeInitList_b6a3[];
extern const u8 nativeInitList_f23a[];
extern const u8 nativeInitList_f23d[];
extern const u8 nativeInitList_f240[];
extern const u8 nativeInitList_f243[];
extern const u8 nativeInitList_f7c6[];
extern const u8 nativeInitList_f7c9[];
extern const u8 nativeInitList_f7cc[];
extern const u8 nativeInitList_fb76[];

// Shared rodata lists used by fade_native_init_046dd0 (also referenced from elsewhere, so not renamed)
extern const u8 data_020f9c7c[];
extern const u8 data_020f9c7f[];
extern const u8 data_020f9c82[];
extern const u8 data_020f9c85[];
extern const u8 data_020f9c88[];

// Cell position pairs (u16 x, u16 y) passed to write_cell
extern u16 cellPos_c0fe[];
extern u16 cellPos_c102[];
extern u16 cellPos_c106[];
extern u16 cellPos_c10a[];
extern u16 cellPos_c10e[];
extern u16 cellPos_c112[];
extern u16 cellPos_c116[];

// Event lists (0xffff terminated) passed to MultiEventSet
extern u16 eventList_e2f8[];
extern u16 eventList_e302[];
extern u16 eventList_e30c[];
extern u16 eventList_e316[];
extern u16 eventList_e320[];
extern u16 eventList_e32a[];
extern u16 eventList_e334[];
extern u16 eventList_e33e[];

// Functions from other units that are not in engine/functions.h (original signatures from original_names.tsv)
void RewCellOne(u16 a, u16 b, u16 c);
void MultiEventSet(u16 *list, u8 a, u8 b, u8 c);

#endif
