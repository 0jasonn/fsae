#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Halfword field: the top two bits select the form (0 none, 0x4000 positive, 0x8000 negated), the low five bits are the
// magnitude. The magnitude is read through a volatile pointer, as the ROM reads the halfword again for each form.
// Field_GetSigned5(field) (0x02012f98): returns the magnitude, negated for the 0x8000 form, and 0 when the form is none.
extern "C" s32 Field_GetSigned5(u16 *field);

ARM s32 Field_GetSigned5(u16 *field) {
    u16 form;

    form = (u16)(*field & 0xc000);
    if (form == 0) {
        return 0;
    }
    if (form == 0x4000) {
        return *(volatile u16 *)field & 0x1f;
    }
    if (form == 0x8000) {
        return -(*(volatile u16 *)field & 0x1f);
    }
    return 0;
}
