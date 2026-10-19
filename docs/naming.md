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

Shared types are `Entity` (`include/engine/entity.h`, original name `OBJ_WORK_`), `PlayerData` / game state
(`include/engine/player.h`, original `PL_WORK_`), every prototype in `include/engine/functions.h`, and any header used by
more than one file.

- An implementer never renames, retypes or adds a field of a shared structure on its own. It proposes the change
  (offset, old name, new name, evidence) in its report and keeps using the current name.
- The reviewer applies the change to the central definition, updates every reference in `src/` and `include/`
  (checked by compiling every file, not by text search alone), rebuilds, verifies the ROM SHA1 and commits it as one
  change.
- The same applies to renaming a function or data symbol used by more than one file.

## Original names come first

- `config/eur/original_names.tsv` lists the original name and C++ signature of about 3,000 functions, recovered from the
  debug build. Use them exactly; invent names only for functions still called `func_XXXXXXXX`.
- The code is C++ (`.cpp`). Shared prototypes live once in `include/engine/functions.h`, with the original parameter types
  (`OBJ_WORK_*` = `Entity *`, `unsigned char` = `u8`, `unsigned short` = `u16`, `long` = `s32`, `unsigned long` = `u32`).
  The build checks them: a definition whose types differ from the declaration gets a different mangled name and fails to
  link. Functions that were unmangled in the original, TwlSDK functions and class methods are in its `extern "C"` block.
- After adding code, `sh tools/build_commit.sh` compiles, runs `tools/cxx_symbols.py` (puts the mangled names into
  `symbols.txt`), links and checks the SHA1.

## Files and variables always get names

- Every file gets a provisional name from the original functions it holds: `em09.cpp` for `em09_*`, `message.cpp` for
  message code; later units of the same module are `em09_2.cpp`, `em09_3.cpp`. Never an address-only name.
- Every local, parameter, file-local struct field and file-local data symbol gets a descriptive provisional name when
  it is written (`unk_` only for bytes nobody reads). File-local data renames (`data_XXXXXXXX newName`) go in the
  renames file; data used by more than one file is proposed, like shared fields.
