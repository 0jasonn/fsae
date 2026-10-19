# Matching tips

Patterns that came up repeatedly while matching game code with mwccarm (DSi 1.2, flags in `tools/configure.py`).
Every DSi compiler version (1.1–1.6sp2) has produced identical code so far; 2.0 does not match.

## Workflow

- `python tools/asm.py START [END]` prints dsd's disassembly for a function or address range.
- `python tools/trymatch.py file.cpp -d` compiles a file (`.c` as C99) and diffs every `func_XXXXXXXX` against the base ROM,
  ignoring relocated bits. `-v dsi/1.1 dsi/1.6sp2 ...` compares compiler versions.
- `python tools/add_unit.py src/... FIRST LAST` adds a complete unit to `delinks.txt`; a unit must be contiguous and
  every function in it must match. Split around non-matching functions and keep the attempt in `docs/nonmatching/`.
- `sh tools/build_commit.sh "message"` rebuilds, checks the ROM SHA1 and commits.

## Codegen patterns

- **Store order is not source order.** Byte/word stores to independent fields are often emitted with the last one
  first, or with bitfield words (`unk_1c`) moved before or after the byte stores. When only the store order differs,
  permute the statements (a small script over `itertools.permutations` finds it quickly).
- **The original writes straight into fields and reads them back.** Prefer
  `e->unk_2b = Random() & 0x18; func(e, e->unk_2a = e->unk_2b >> 3);` over locals; the compiler forwards the stored
  value. The reverse also happens: a value kept in a register across a call means the source had a local.
- **`u8` locals** fix many register-allocation differences (random values, loop counters, indices).
- **Declaration order of locals changes register allocation.** Declaring the loop counter first
  (`u8 i; ... for (i = 0; ...)`) often fixes swapped registers.
- An `and rX, rX, #0xff` before passing a value to a `u8` parameter means the value came from an `int` temporary.
- `int x = ...; int y = ...; f(e, x, y);` when each argument is fully computed before the next call.
- Argument order of the direction helpers varies (`func_02086078(a, b)` is called both ways); check `r0`/`r1`.
- A conditional executed with `movne`/`strbne` before a branch over the other arm usually means the `if` tests the
  other condition (`if (x == 2) {...} else {...}`).
- Single shared `return FALSE` blocks come from structured `if/else` nesting rather than early returns.
- `(u16)(x - 0x1f7) <= 2` is the original range check for "x is within 1 of 0x1f8".
- `ABS(a) - ABS(b) <= 0` compiles to the `rsbmi`/`rsblt` pairs seen in follower code.

## Types

- `Entity` (`include/Unknown/Entity.h`) holds the fields shared by all actors; from about 0x60 the layout depends on
  the actor, so each file overlays its own `Vars_*` struct with `VARS(type, e)`.
- Positions are 16.16 fixed point (`FixedPoint`) at 0x30/0x34/0x38; most code uses the integer half.
- `unk_1c` is a bitfield word (`b0:2 b2:2 b4:2 b6:2 b8:6 b14:2 b16:4 b20:4 b24:6 b30:2`).
- `_u32_div_f` (0x0200db54) is the runtime unsigned divide that `%`/`/` on unsigned values call.
- **Initialised local arrays** (`u16 ids[8] = {...}`) copy from a rodata table. Give the table its ROM name as a global
  `const` struct, copy it (`TelopIdList list = data_020d7c50;`), index `list.ids[i]`, and add the table's range as a
  `.rodata` line on the unit in `delinks.txt` (see `src/game/message_02049f38.c`).
- **trymatch checks ARM call targets**: a `bl` to the wrong function (or `_s32_div_f` where the original calls
  `_u32_div_f`) is reported as `call at +0x.. goes to X, the original calls 0x..`. Unsigned operands (`(u32)x % n`)
  give the unsigned divide helper.
