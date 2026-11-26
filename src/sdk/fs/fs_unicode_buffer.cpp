#include "global.h"
#include "types.h"
#include "engine/functions.h"
#include "sdk/fs/fs_api.h"

void FSi_ReleaseUnicodeBuffer(void *buffer) {
    if (buffer == NULL) {
        return;
    }
    OS_SendMessage(data_02128b4c, buffer, 1);
}
