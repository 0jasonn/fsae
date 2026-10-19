#include "engine/functions.h"
#include "game/fade_native.h"
#include "global.h"

// fade_native_init_* (0x020465ec to 0x0204700c): each routine picks block lists with RandomBlockSet.
// Renamed here: fade_native_init_0467d0 -> fade_native_init_0467d0, fade_native_init_046a70 -> fade_native_init_046a70,
// fade_native_init_046dd0 -> fade_native_init_046dd0.

ARM void fade_native_init_0465ec(u8 param) {
    u8 roll = Random();
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_4306, 0);
    } else {
        RandomBlockSet(nativeInitList_430d, 0);
    }
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_42f1, 0);
    } else {
        RandomBlockSet(nativeInitList_42ea, 0);
    }
    if (roll < 0x55) {
        RandomBlockSet(nativeInitList_42ff, 0);
        RandomBlockSet(nativeInitList_4314, 0);
    } else if (roll < 0xaa) {
        RandomBlockSet(nativeInitList_42ff, 0);
        RandomBlockSet(nativeInitList_42f8, 0);
    } else {
        RandomBlockSet(nativeInitList_4314, 0);
        RandomBlockSet(nativeInitList_42f8, 0);
    }
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_42e7, 0);
    } else {
        RandomBlockSet(nativeInitList_42e4, 0);
    }
}

ARM void fade_native_init_0466cc(u8 param) {
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_4325, param);
    } else {
        RandomBlockSet(nativeInitList_431c, param);
    }
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_4322, param);
    } else {
        RandomBlockSet(nativeInitList_431f, param);
    }
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_432f, param);
    } else {
        RandomBlockSet(nativeInitList_4328, param);
    }
}

ARM void fade_native_init_046758(u8 param) {
    u8 roll = Random();
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_433b, 0);
    } else {
        RandomBlockSet(nativeInitList_4341, 0);
    }
    if (roll < 0x55) {
        RandomBlockSet(nativeInitList_4344, 0);
    } else if (roll < 0xaa) {
        RandomBlockSet(nativeInitList_4338, 0);
    } else {
        RandomBlockSet(nativeInitList_433e, 0);
    }
}

ARM void fade_native_init_0467d0(u8 param) {
    switch (Random() % 6) {
    case 0:
        RandomBlockSet(nativeInitList_4348, param);
        RandomBlockSet(nativeInitList_4351, param);
        break;
    case 1:
        RandomBlockSet(nativeInitList_4348, param);
        RandomBlockSet(nativeInitList_434e, param);
        break;
    case 2:
        RandomBlockSet(nativeInitList_4348, param);
        RandomBlockSet(nativeInitList_434b, param);
        break;
    case 3:
        RandomBlockSet(nativeInitList_4351, param);
        RandomBlockSet(nativeInitList_434e, param);
        break;
    case 4:
        RandomBlockSet(nativeInitList_4351, param);
        RandomBlockSet(nativeInitList_434b, param);
        break;
    case 5:
        RandomBlockSet(nativeInitList_434e, param);
        RandomBlockSet(nativeInitList_434b, param);
        break;
    }
}

ARM void fade_native_init_0468d4(u8 param) {
    switch (Random() % 3) {
    case 0:
        RandomBlockSet(nativeInitList_6f52, param);
        RandomBlockSet(nativeInitList_6f5c, param);
        break;
    case 1:
        RandomBlockSet(nativeInitList_6f52, param);
        RandomBlockSet(nativeInitList_6f57, param);
        break;
    case 2:
        RandomBlockSet(nativeInitList_6f5c, param);
        RandomBlockSet(nativeInitList_6f57, param);
        break;
    }
}

ARM void fade_native_init_046974(u8 param) {
    u8 roll;
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_43a3, 0);
    } else {
        RandomBlockSet(nativeInitList_436f, 0);
    }
    roll = Random();
    if (roll < 0x55) {
        RandomBlockSet(nativeInitList_437c, 0);
        RandomBlockSet(nativeInitList_4389, 0);
        RandomBlockSet(nativeInitList_4354, 0);
        RandomBlockSet(nativeInitList_435d, 0);
    } else if (roll < 0xaa) {
        RandomBlockSet(nativeInitList_437c, 0);
        RandomBlockSet(nativeInitList_4396, 0);
        RandomBlockSet(nativeInitList_4354, 0);
        RandomBlockSet(nativeInitList_4366, 0);
    } else {
        RandomBlockSet(nativeInitList_4389, 0);
        RandomBlockSet(nativeInitList_4396, 0);
        RandomBlockSet(nativeInitList_435d, 0);
        RandomBlockSet(nativeInitList_4366, 0);
    }
}

ARM void fade_native_init_046a70(u8 param) {
    u8 roll = Random();
    if (roll < 0x40) {
        RandomBlockSet(nativeInitList_43bd, 0);
        RandomBlockSet(nativeInitList_43ca, 0);
        RandomBlockSet(nativeInitList_43d7, 0);
    } else if (roll < 0x80) {
        RandomBlockSet(nativeInitList_43bd, 0);
        RandomBlockSet(nativeInitList_43ca, 0);
        RandomBlockSet(nativeInitList_43b0, 0);
    } else if (roll < 0xc0) {
        RandomBlockSet(nativeInitList_43bd, 0);
        RandomBlockSet(nativeInitList_43d7, 0);
        RandomBlockSet(nativeInitList_43b0, 0);
    } else {
        RandomBlockSet(nativeInitList_43ca, 0);
        RandomBlockSet(nativeInitList_43d7, 0);
        RandomBlockSet(nativeInitList_43b0, 0);
    }
}

ARM void fade_native_init_046b48(u8 param) {
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_4408, param);
    } else {
        RandomBlockSet(nativeInitList_4405, param);
    }
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_43f0, param);
    } else {
        RandomBlockSet(nativeInitList_43ed, param);
    }
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_43e4, param);
    } else {
        RandomBlockSet(nativeInitList_4414, param);
    }
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_43ea, param);
    } else {
        RandomBlockSet(nativeInitList_4402, param);
    }
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_43f6, param);
    } else {
        RandomBlockSet(nativeInitList_43f3, param);
    }
    switch (Random() % 3) {
    case 0:
        RandomBlockSet(nativeInitList_4411, param);
        break;
    case 1:
        RandomBlockSet(nativeInitList_440e, param);
        break;
    case 2:
        RandomBlockSet(nativeInitList_43e7, param);
        break;
    }
    switch (Random() & 3) {
    case 0:
        RandomBlockSet(nativeInitList_43ff, param);
        break;
    case 1:
        RandomBlockSet(nativeInitList_440b, param);
        break;
    case 2:
        RandomBlockSet(nativeInitList_43fc, param);
        break;
    case 3:
        RandomBlockSet(nativeInitList_43f9, param);
        break;
    }
}

ARM void fade_native_init_046cec(u8 param) {
    switch (Random() & 3) {
    case 0:
        RandomBlockSet(nativeInitList_4421, param);
        break;
    case 1:
        RandomBlockSet(nativeInitList_4435, param);
        break;
    case 2:
        RandomBlockSet(nativeInitList_442a, param);
        break;
    case 3:
        RandomBlockSet(nativeInitList_4418, param);
        break;
    }
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_9349, param);
    } else {
        RandomBlockSet(nativeInitList_9364, param);
    }
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_935b, param);
    } else {
        RandomBlockSet(nativeInitList_9352, param);
    }
    if (Random() & 1) {
        RandomBlockSet(nativeInitList_9340, param);
    } else {
        RandomBlockSet(nativeInitList_932e, param);
    }
}

ARM void fade_native_init_046dd0(u8 param) {
    switch (Random() & 7) {
    case 0:
        RandomBlockSet(data_020f9c7c, param);
        RandomBlockSet(data_020f9c85, param);
        RandomBlockSet(data_020f9c82, param);
        break;
    case 1:
        RandomBlockSet(data_020f9c7c, param);
        RandomBlockSet(data_020f9c85, param);
        RandomBlockSet(data_020f9c88, param);
        break;
    case 2:
        RandomBlockSet(data_020f9c7c, param);
        RandomBlockSet(data_020f9c85, param);
        RandomBlockSet(data_020f9c7f, param);
        break;
    case 3:
        RandomBlockSet(data_020f9c7c, param);
        RandomBlockSet(data_020f9c82, param);
        RandomBlockSet(data_020f9c88, param);
        break;
    case 4:
        RandomBlockSet(data_020f9c7c, param);
        RandomBlockSet(data_020f9c82, param);
        RandomBlockSet(data_020f9c7f, param);
        break;
    case 5:
        RandomBlockSet(data_020f9c7c, param);
        RandomBlockSet(data_020f9c88, param);
        RandomBlockSet(data_020f9c7f, param);
        break;
    case 6:
        RandomBlockSet(data_020f9c85, param);
        RandomBlockSet(data_020f9c82, param);
        RandomBlockSet(data_020f9c7f, param);
        break;
    case 7:
        RandomBlockSet(data_020f9c85, param);
        RandomBlockSet(data_020f9c88, param);
        RandomBlockSet(data_020f9c7f, param);
        break;
    case 8:
        RandomBlockSet(data_020f9c82, param);
        RandomBlockSet(data_020f9c88, param);
        RandomBlockSet(data_020f9c7f, param);
        break;
    }
}

ARM void fade_native_init_046f8c(u8 param) {
    u8 roll = Random();
    if (roll < 0x55) {
        RandomBlockSet(nativeInitList_444e, param);
        RandomBlockSet(nativeInitList_4440, param);
    } else if (roll < 0xaa) {
        RandomBlockSet(nativeInitList_444e, param);
        RandomBlockSet(nativeInitList_4447, param);
    } else {
        RandomBlockSet(nativeInitList_4440, param);
        RandomBlockSet(nativeInitList_4447, param);
    }
}

ARM void fade_native_init_04700c(u8 param) {
    switch (Random() & 3) {
    case 0:
        RandomBlockSet(nativeInitList_b69e, param);
        RandomBlockSet(nativeInitList_b6a3, param);
        RandomBlockSet(nativeInitList_b699, param);
        break;
    case 1:
        RandomBlockSet(nativeInitList_b69e, param);
        RandomBlockSet(nativeInitList_b6a3, param);
        RandomBlockSet(nativeInitList_b694, param);
        break;
    case 2:
        RandomBlockSet(nativeInitList_b69e, param);
        RandomBlockSet(nativeInitList_b699, param);
        RandomBlockSet(nativeInitList_b694, param);
        break;
    case 3:
        RandomBlockSet(nativeInitList_b6a3, param);
        RandomBlockSet(nativeInitList_b699, param);
        RandomBlockSet(nativeInitList_b694, param);
        break;
    }
}
