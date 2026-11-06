#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"

// Functions in this file (address -> name, pending reviewer apply to symbols.txt):
//   msgOpen -> msgOpen
//   tlpOpen -> tlpOpen
//   msgClose -> msgClose
//   tlpClose -> tlpClose

// Work blocks in the bss, accessed by byte offset
extern u8 messageBox[];
extern u8 telopBox[];


// Scene state handlers: a table entry returns 0 when the state is done
int msgOpen(void) {
    if (messageBox[0xe3] != 1) {
        messageBox[0xe3] = 1;
        SoundReq(0x43);
    }
    statusUpdate((MSG_STATUS)2);
    if (msgWinSizeChange(1) != 0) {
        messageBox[0xd0] = 3;
    }
    return 0;
}

int tlpOpen(void) {
    if (telopUpdate(-1) != 0) {
        telopBox[0xd0] = 3;
    }
    return 0;
}

int msgClose(void) {
    if (messageBox[0xe3] != 3) {
        messageBox[0xe3] = 3;
        messageBox[0xaf] = 0;
        messageBox[0xae] = 0;
        messageBox[0xad] = 0;
        messageBox[0xac] = 0;
        SoundReq(0x44);
    }
    statusUpdate((MSG_STATUS)7);
    if (msgWinSizeChange(-1) != 0) {
        messageBox[0xd0] = 5;
    }
    return 0;
}

int tlpClose(void) {
    if (telopUpdate(1) != 0) {
        telopBox[0xd0] = 5;
    }
    return 0;
}
