#include "engine/functions.h"
#include "global.h"
#include "game/eff.h"

// Effect work table and cut effects, 0x0209b79c to 0x0209b8c0 (eff_fade_out parked).

// effwk_add() (0x0209b79c): appends a zeroed entry to the table and returns it.
ARM EffWork *effwk_add(void) {
    EffWork *work = (EffWork *)data_0217d190 + data_0217d18c;

    MI_CpuFill8(work, 0, 16);
    data_0217d18c++;
    return work;
}

// effwk_del(EffWork*, long) (0x0209b7dc): moves the entries after index down over the removed one.
ARM void effwk_del(void *work, s32 index) {
    MI_CpuCopy8(work, (u8 *)work + 0x10, (data_0217d18c - (index + 1)) << 4);
    data_0217d18c--;
}

// eff_cut_out(void*, long) (0x0209b810): cut out effect, removes the entry.
ARM int eff_cut_out(void *work, s32 index) {
    *(s32 *)(data_0217d23c + 0xf8) = -16;
    effwk_del(work, index);
    return 1;
}

// eff_cut_in_init() (0x0209b830): adds a cut in entry.
ARM void eff_cut_in_init(void) {
    EffWork *work;

    *(s32 *)(data_0217c23c + 0xf50) = 0;
    work = effwk_add();
    work->kind = 2;
    *(s32 *)(data_0217d23c + 0xf8) = 0;
}

// eff_cut_in(void*, long) (0x0209b860): cut in effect, removes the entry.
ARM int eff_cut_in(void *work, s32 index) {
    *(s32 *)(data_0217d23c + 0xf8) = 0;
    effwk_del(work, index);
    return 1;
}

// eff_fade_out_init(long) (0x0209b880): adds a fade out entry that darkens by speed each frame.
ARM void eff_fade_out_init(s32 speed) {
    EffWork *work;

    *(s32 *)(data_0217c23c + 0xf50) = 0;
    work = effwk_add();
    work->kind = 3;
    work->level = 0;
    work->speed = -speed;
    *(s32 *)(data_0217d23c + 0xf8) = work->level >> 12;
}
