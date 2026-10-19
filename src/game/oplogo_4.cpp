#include "engine/functions.h"
#include "global.h"

typedef struct OplogoShadowBlock {
    /* 00 */ u8 unk_00[0xc];
    /* 0c */ s16 scrollOffset; // guess: horizontal offset written by oplogo_info
} OplogoShadowBlock;
extern OplogoShadowBlock data_0212c75c;
extern u8 data_0212c4dc;

ARM void oplogo_fadeOff(Entity *e) {
    e->spriteSettings.b0 = 0;
}

ARM void oplogo_info(Entity *e) {
    s16 offset = data_0212c75c.scrollOffset;
    e->action = 1;
    if (data_0212c4dc == 4) {
        if (offset < -0x90) {
            offset = offset + 8;
        }
    } else {
        if (offset > -0xc0) {
            offset = offset - 8;
        }
    }
    data_0212c75c.scrollOffset = offset;
}
