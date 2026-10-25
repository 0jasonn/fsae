#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/lobby.h"

// Functions in this file (provisional names):
//   lobby_callWithZeroPos (0x020b5214), lobby_stepAndCall (0x020b523c)

// lobby_callWithZeroPos(self, arg) (0x020b5214, provisional name): when the object at +4 of self exists, calls
// func_020b5744 with it, arg and a zero position (two halfwords)
extern "C" void func_020b5744(void *obj, void *arg, s16 *pos);
extern "C" void lobby_callWithZeroPos(void *self, void *arg);
ARM void lobby_callWithZeroPos(void *self, void *arg) {
    s16 pos[2];

    if (*(void **)((u8 *)self + 4) == NULL) {
        return;
    }
    pos[0] = 0;
    pos[1] = 0;
    func_020b5744(*(void **)((u8 *)self + 4), arg, pos);
}

// lobby_stepAndCall(self, arg) (0x020b523c, provisional name): calls func_020b5264 and then func_020b57f4 with the object
// at +4 of self when it exists
extern "C" void func_020b5264(void *self, void *arg);
extern "C" void func_020b57f4(void *obj, void *arg);
extern "C" void lobby_stepAndCall(void *self, void *arg);
ARM void lobby_stepAndCall(void *self, void *arg) {
    func_020b5264(self, arg);
    if (*(void **)((u8 *)self + 4) == NULL) {
        return;
    }
    func_020b57f4(*(void **)((u8 *)self + 4), arg);
}
