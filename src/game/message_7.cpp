#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"

// Functions in this file (address -> name, pending reviewer apply to symbols.txt):
//   msgOpen -> msgOpen
//   tlpOpen -> tlpOpen
//   msgClose -> msgClose
//   tlpClose -> tlpClose

// Work blocks in the bss, accessed by byte offset
extern u8 data_0217d39c[];
extern u8 data_0217d484[];


// Scene state handlers: a table entry returns 0 when the state is done
ARM int msgOpen(void) {
    if (data_0217d39c[0xe3] != 1) {
        data_0217d39c[0xe3] = 1;
        SoundReq(0x43);
    }
    statusUpdate((MSG_STATUS)2);
    if (msgWinSizeChange(1) != 0) {
        data_0217d39c[0xd0] = 3;
    }
    return 0;
}

ARM int tlpOpen(void) {
    if (telopUpdate(-1) != 0) {
        data_0217d484[0xd0] = 3;
    }
    return 0;
}

ARM int msgClose(void) {
    if (data_0217d39c[0xe3] != 3) {
        data_0217d39c[0xe3] = 3;
        data_0217d39c[0xaf] = 0;
        data_0217d39c[0xae] = 0;
        data_0217d39c[0xad] = 0;
        data_0217d39c[0xac] = 0;
        SoundReq(0x44);
    }
    statusUpdate((MSG_STATUS)7);
    if (msgWinSizeChange(-1) != 0) {
        data_0217d39c[0xd0] = 5;
    }
    return 0;
}

ARM int tlpClose(void) {
    if (telopUpdate(1) != 0) {
        data_0217d484[0xd0] = 5;
    }
    return 0;
}
