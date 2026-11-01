#include "engine/functions.h"
#include "knife/comm/wxc.h"

// WXC_GetStateCode (0x020280d0): returns the state code word at +0x08 of the comm state block.
s32 WXC_GetStateCode(void) {
    return *(s32 *)(data_0212c9a8 + 0x8);
}
