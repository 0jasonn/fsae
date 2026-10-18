# Patched dsd

The released `dsd` (v0.12.1) and `ds-rom` (v0.8.0) can't handle this game yet, so `tools/dsd.exe` is built from source
with the two patches in this folder.

| Patch | Applies to | Base commit |
| --- | --- | --- |
| `ds-rom-dsiware.patch` | [AetiasHax/ds-rom](https://github.com/AetiasHax/ds-rom) | `b9c34305` ("DSi enhanced support", unreleased) |
| `ds-decomp-twl.patch` | [AetiasHax/ds-decomp](https://github.com/AetiasHax/ds-decomp) | `c4080635` (v0.12.1) |

## What they fix

`ds-rom-dsiware.patch` (DSiWare layout):
- DSiWare has no DS/DSi region boundary in the header (`0x90` is zero), the DSi area starts where the DS area ends.
  Extract and build use that layout instead of failing.
- The header's reserved bytes at `0x1000..0x4000` are non-zero on DSiWare and are preserved in
  `dsi/header_reserved.bin`.
- DSiWare isn't padded to a cartridge capacity, the file ends at the end of the DSi area.

`ds-decomp-twl.patch` (TwlSDK and build fixes):
- Uses the patched `ds-rom` via `[patch.crates-io]`, and passes the new DSi/footer fields through `rom config`.
- TwlSDK's crt0 calls `INITi_CallStaticInitializers` after `__call_static_initializers`, so the `.ctor` search falls
  back to earlier calls in the entry function until it finds one pointing into ARM9.
- An empty `.exceptix` table (no C++ exceptions) is treated as no exception data instead of a zero-size section.
- Thumb `b` instructions no longer get `arm_branch` relocations, which the linker re-encoded as ARM instructions.

## Rebuilding dsd

Needs Rust (`x86_64-pc-windows-gnu`) and MinGW-w64 on `PATH` (for `dlltool`).

```bash
git clone https://github.com/AetiasHax/ds-rom.git && git -C ds-rom checkout b9c34305
git clone https://github.com/AetiasHax/ds-decomp.git && git -C ds-decomp checkout c4080635
git -C ds-rom apply ../tools/patches/ds-rom-dsiware.patch
git -C ds-decomp apply ../tools/patches/ds-decomp-twl.patch
cd ds-decomp && cargo build --release -p ds-decomp-cli
```

The two clones must sit side by side, since the patch points `ds-decomp` at `../ds-rom/lib`. Copy
`target/release/dsd.exe` to `tools/dsd.exe`.
