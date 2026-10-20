#include "engine/functions.h"
#include "global.h"
#include "object/tama11.h"

// Command queue runner, 0x02080ca4. The queue lives in data_0212ccb0 at a half selected by data_0212c4c8; each byte of
// the queue names a handler in queueHandlerTable, which takes the cursor and returns the next one. Handlers run until the
// cursor reaches the end stored in data_0212c570; then that end is set to the start of the half for the next pass.
typedef u8 *(*QueueHandler)(u8 *cursor);
extern u8 data_0212ccb0[];
extern u8 data_0212c4c8;
extern u32 data_0212c570;
extern const QueueHandler queueHandlerTable[];

// func_02080ca4 (0x02080ca4)
ARM void func_02080ca4(void) {
    u8 *cursor;
    u8 cmd;

    cursor = data_0212ccb0 + ((data_0212c4c8 ^ 1) << 8);
    if ((u32)cursor < data_0212c570) {
        do {
            cmd = *cursor++;
            cursor = queueHandlerTable[cmd](cursor);
        } while ((u32)cursor < data_0212c570);
    }
    data_0212c570 = (u32)(data_0212ccb0 + ((data_0212c4c8 ^ 1) << 8));
}
