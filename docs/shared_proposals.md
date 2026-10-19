# Open proposals for shared types

Collected from implementer reports; apply with tools/rename_field.py (fields) or by reconciling declarations, one change
per commit, ROM SHA1 verified.

- `data_0212c648`: declared `Entity *` in boss headers but read as a struct (u16 at +0x18/+0x1a, +0x20/+0x22) elsewhere.
  Needs one central declaration.
- `data_0212c5ac`: fade/blend control. 0x00 blendEnabled, 0x01 blendMode, 0x07 blendColor, 0x08 blendWeight (s16),
  0x0c resetValue (s32).
- `data_0212c5bc` (u16 vs u8[] at +0x12) and `data_0212c618` (u8 vs u8[]): conflicting declarations.
- Game state `data_0212c7c8` (Player.h `UnkStruct_0212c7c8`, State_C.h `GameStateC`, GameStateView_C.h): unify into one
  struct of at least 0xa0 bytes. Proposed fields from implementer C: 0x01 pickIndex, 0x02 active, 0x03 phase,
  0x04 phaseTimer, 0x05 periodicFlag, 0x06 difficulty, 0x07 gameMode, 0x08 score, 0x0c playerCounters[4],
  0x1c frameCount, 0x26 musicId, 0x28 slots[4] (8 bytes), 0x4e usedPickMask, 0x4f phaseFlags, 0x8e trackVariant.
- Entity 0x08/0x09: entity-list tag pair used with `type`; Entity 0x3c bit 0x80 looks like an invulnerability flag;
  Entity 0x70..0x72 used as parent flags / direction step by several actors in 0x0204xxxx.
- PlayerData byte at 0x05 (flag read by Entity_UpdateSubActionFromPlayers).
- Function prefixes `Boss_` / `Enemy_` are generic and should become actor names once actors are identified.

## Round 3 proposals (not applied yet)

- `Entity.spriteSettings`: split `b8:6` into `b8:2` + `b10:4` (B, func_020417e8 writes bits 8-9 only); split `b2:2` into two 1-bit fields (C, func_02049dac copies bits 2 and 3 separately).
- `Entity` 0x2c `unk_2c` -> `probeFlags` (A, func_02039f24 tests 0xe/0xe0/0xe00/0xe000 before wall probes).
- `Entity` 0x64 -> `Entity *target` (B, func_02041f48); 0x3d `iframes` is read signed (B, D).
- `PlayerData` 0x2c -> `Entity *shadow`, 0x0f -> `shadowFlags` (C, func_02049cdc/func_02049dac); 0x36 is a u16 flags word (A, B: bits 0x2, 0x10, 0x100); 0x05 blocks targeting (B).
- `UnkStruct_0212c7c8`: unk_0 is the player count (A, B, D); +0x48 `trackIndex` (C); +0x8e track variant, struct must grow to >= 0x8f (A).
- `data_0212c648`: u16 grid origin at +0x18/+0x1a (A, B), Entity* camera target at +0 (D).
- `data_02104a20` is RAM, not const (D). `data_0211474c` is used as both a function table and a struct (D, needs checking).
- New blocks seen: data_02134b48 (B), data_02134980, data_02134d3c (D), data_0217d36c/84/9c, data_0217d484, data_0216efbc, data_0210389c, data_0212c67c (C). Details in the implementers' file-local types.
