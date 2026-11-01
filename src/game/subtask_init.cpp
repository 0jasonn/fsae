#include "engine/functions.h"
#include "game/subtask_d.h"
#include "global.h"
#include "types.h"

// subTaskInit_lang (0x0209bbb4): frees the block of the previous language, loads the compressed subtask file of the
// language (ten entries, "./subtask_<region>_<lang>.cmp"), decompresses it into a new global buffer and keeps the
// buffer in data_0212c560.

extern void *data_0212c560;

extern "C" void subTaskInit_lang(int language);
ARM void subTaskInit_lang(int language) {
    u32 size;
    void *file;
    void *block;

    if (data_0212c560 != 0) {
        func_0208e188(data_0212c560);
        data_0212c560 = 0;
    }
    switch (language) {
    case 0:
        file = loadFile(&size, "./subtask_jp.cmp", -32);
        break;
    case 1:
        file = loadFile(&size, "./subtask_us_en.cmp", -32);
        break;
    case 2:
        file = loadFile(&size, "./subtask_eu_en.cmp", -32);
        break;
    case 3:
        file = loadFile(&size, "./subtask_eu_gr.cmp", -32);
        break;
    case 4:
        file = loadFile(&size, "./subtask_eu_fr.cmp", -32);
        break;
    case 5:
        file = loadFile(&size, "./subtask_us_fr.cmp", -32);
        break;
    case 6:
        file = loadFile(&size, "./subtask_eu_sp.cmp", -32);
        break;
    case 7:
        file = loadFile(&size, "./subtask_us_sp.cmp", -32);
        break;
    case 8:
        file = loadFile(&size, "./subtask_eu_it.cmp", -32);
        break;
    case 9:
        file = loadFile(&size, "./subtask_eu_du.cmp", -32);
        break;
    }
    block = EL_GetGlobalAdr(*(u32 *)file >> 8, 4);
    MI_UncompressLZ16(file, block);
    func_0208e188(file);
    data_0212c560 = block;
}
