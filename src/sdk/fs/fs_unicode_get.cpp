#include "global.h"
#include "types.h"
#include "sdk/fs/fs_api.h"
#include "sdk/fs/stdconv_wrap_api.h"
#include "sdk/os/os_interrupts.h"
#include "sdk/os/os_message.h"

u16 *FSi_GetUnicodeBuffer(const char *path) {
    u16 *buffer;
    u32 irqState;
    s32 index;
    s32 length;

    index = 0;
    buffer = NULL;
    irqState = OS_DisableInterrupts();
    if (data_02128b38 == 0) {
        data_02128b38 = 1;
        OS_InitMessageQueue(&data_02128b4c, data_02128b3c, 4);
        for (index = 0; index < 4; index++) {
            OS_SendMessage(&data_02128b4c, data_02128b6c[index], 1);
        }
    }
    OS_RestoreInterrupts(irqState);
    OS_ReceiveMessage(&data_02128b4c, (void **)&buffer, 1);
    if (path != NULL) {
        length = 0x115;
        StdConv_SjisToUnicode(buffer, &length, (void *)path, NULL, NULL);
        buffer[length] = 0;
    }
    return buffer;
}
