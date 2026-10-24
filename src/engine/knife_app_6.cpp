#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/m4a.h"

// KnifeApp::getCurrentLanguage (0x0208dfa4): the language entry of the table at data_020dd9ac, chosen by the byte at
// data_021348d8
extern s32 data_020dd9ac[];
extern u8 data_021348d8[];
extern "C" s32 KnifeApp_getCurrentLanguage(void *self);
ARM s32 KnifeApp_getCurrentLanguage(void *self) {
    return data_020dd9ac[data_021348d8[0]];
}

// KnifeApp_getField20Address (0x0208dfc0): the address of the 0x20 field of the application object
extern "C" void *KnifeApp_getField20Address(void *self);
ARM void *KnifeApp_getField20Address(void *self) {
    return (u8 *)self + 0x20;
}
