#include "engine/functions.h"
#include "global.h"

// func_02082c54 (0x02082c54): stores its argument as the callback in data_02171e20 (the callback slot used by
// knifeExitCallback and the ResourceCtrl setup).
extern u32 data_02171e20;

// func_02082c54 (0x02082c54)
ARM void func_02082c54(void *fn) {
    data_02171e20 = (u32)fn;
}
