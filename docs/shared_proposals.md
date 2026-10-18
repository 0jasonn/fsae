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
