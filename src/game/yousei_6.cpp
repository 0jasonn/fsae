#include "engine/functions.h"
#include "enemy/loader_decls.h"

// YouseiDemoLoad (0x0204d50c): loads the frame record of the current demo, then the room, the events and the frame.
extern "C" void YouseiDemoLoad(void);

ARM void YouseiDemoLoad(void) {
    FRAME_INFO_ *frame;

    frame = youseiFrameTable[data_0212c7c8.unk_1[0]];
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
