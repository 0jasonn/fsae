# Naming policy

Names are inferred from behaviour (the ROM has no symbols). Mark guesses with a short comment when unsure.
Conventions follow the Minish Cap decomp (TMC) where the role matches.

## Names are given when code is written, not later

- **Locals and parameters:** always descriptive (`target`, `anim`, `count`), never `r0`/`tmp`.
- **Actor-specific fields** (the file's own `Vars_*` overlay): descriptive names right away. The overlay is file-local,
  so this is safe.
- **Functions defined in the file:** give each one a descriptive name (`Octorok_Init`, `Octorok_Action1`) and list
  the `func_XXXXXXXX -> Name` mapping in the file's header comment and in the implementer's report. The reviewer applies
  it to `config/eur/arm9/symbols.txt` and every reference before building. Until then the code keeps the dsd name.
- **Actor files** are named after the actor once it is identified (`Octorok.c`); `kind_ADDR.c` until then.

## Shared structures are only changed centrally

Shared types are `Entity` (`include/Unknown/Entity.h`), `PlayerData` / game state (`include/Unknown/Player.h`), and any
header used by more than one file.

- An implementer never renames, retypes or adds a field of a shared structure on its own. It proposes the change
  (offset, old name, new name, evidence) in its report and keeps using the current name.
- The reviewer applies the change to the central definition, updates every reference in `src/` and `include/`
  (checked by compiling every file, not by text search alone), rebuilds, verifies the ROM SHA1 and commits it as one
  change.
- The same applies to renaming a function or data symbol used by more than one file.
