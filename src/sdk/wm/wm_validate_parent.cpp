#include "sdk/wm/wm_validate_parent.h"

typedef struct WMParentParameter {
    u8 unk_00[4];
    u16 unk_04;
    u8 unk_06[0x12];
    u16 unk_18;
    u8 unk_1a[0x18];
    u16 unk_32;
} WMParentParameter;

// Provisional name. Check the parent parameter limits used by the SDK.
BOOL WMi_ValidateParentParameter(const void *parameter) {
    const WMParentParameter *param = (const WMParentParameter *)parameter;
    if (param->unk_04 > 0x70) {
        return FALSE;
    }
    if (param->unk_18 < 0xa || param->unk_18 > 0x3e8) {
        return FALSE;
    }
    if (param->unk_32 < 1 || param->unk_32 > 0xe) {
        return FALSE;
    }
    return TRUE;
}
