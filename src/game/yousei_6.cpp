#include "engine/functions.h"
#include "actor/enemy/demo_loader.h"

// YouseiDemoLoad (0x0204d50c): loads the frame record of the current demo, then the room, the events and the frame.
extern "C" void YouseiDemoLoad(void);

void YouseiDemoLoad(void) {
    FRAME_INFO_ *frame;

    frame = youseiFrameTable[gameState.unk_01];
    data_02134968[0] = frame->infoRows;
    MultiRoomInit(frame->roomNo);
    FrameSet(frame->frameNo);
    if (GetInfoAdrs(0, 0) != 0) {
        MultiEventSet((u16 *)GetInfoAdrs(0, 0), 0, 0, 0);
    }
    MultiRoomSet();
    data_021348f4[data_0212c4c8] = 1;
    func_0208309c();
}
