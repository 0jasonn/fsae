#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/set_init.h"

// Actor setup (module set). Address -> name:
//   0x02057614 SetInit (original name): applies the sprite and palette settings of the setup tables to a new actor

void SetInit(Entity *e) {
    const u16 *rec;
    u16 colorInfo;

    if (e->unk_19 & 1) {
        return;
    }
    rec = &setInitTable[e->objId * 3];
    if (rec[0] == 0xfffe) {
        return;
    }
    if (rec[0] == 0xffff) {
        rec = setInitSubTables[rec[1]] + e->type * 3;
    }
    if (rec[0] != 0) {
        if (rec[0] & 0x8000) {
            e->unk_20 = rec[0];
            e->spriteSettings.b6 = (u8)((rec[0] & 0x300) >> 8);
        } else {
            GetVGroup(e, rec[0]);
        }
    }
    colorInfo = rec[1];
    if (colorInfo & 0x8000) {
        if (colorInfo != 0x80ff) {
            e->spriteSettings.b20 = colorInfo;
            e->spriteSettings.b16 = e->spriteSettings.b20;
        }
        if (data_0212c7c8.unk_8e == 2) {
            if (e->objId == 0 || e->objId == 0xb) {
                switch (e->type) {
                case 1:
                case 6:
                    e->spriteSettings.b20 = 4;
                    e->spriteSettings.b16 = e->spriteSettings.b20;
                    break;
                case 2:
                case 8:
                    e->spriteSettings.b20 = 3;
                    e->spriteSettings.b16 = e->spriteSettings.b20;
                    break;
                case 3:
                case 9:
                    e->spriteSettings.b20 = 2;
                    e->spriteSettings.b16 = e->spriteSettings.b20;
                    break;
                case 10:
                    e->spriteSettings.b20 = 2;
                    e->spriteSettings.b16 = e->spriteSettings.b20;
                    break;
                case 11:
                    e->spriteSettings.b20 = 3;
                    e->spriteSettings.b16 = e->spriteSettings.b20;
                    break;
                case 12:
                    e->spriteSettings.b20 = 4;
                    e->spriteSettings.b16 = e->spriteSettings.b20;
                    break;
                }
            }
        } else if (data_0212c7c8.unk_8e == 3 && e->objId == 1 && e->unk_20 != 0x60 && (e->type == 3 || e->type == 0x17)) {
            e->spriteSettings.b20 = 5;
            e->spriteSettings.b16 = e->spriteSettings.b20;
        }
    } else {
        e->spriteSettings.b20 = GetObjColor(colorInfo);
        e->spriteSettings.b16 = e->spriteSettings.b20;
    }
    e->unk_1b = rec[2];
    e->unk_19 = 1;
    e->unk_23 = 0;
    e->unk_40 = 0x38;
    func_0208ae78(e);
}
