#include "engine/functions.h"
#include "ui/staffroll.h"
#include "actor/enemy/demo_loader.h"


void StaffrollLoad(void) {
    data_02134968[0] = staffrollFrameInfo.infoRows;
    MPlayerSet(&staffrollFrameInfo);
    MultiRoomInit(staffrollFrameInfo.roomNo);
    FrameSet(staffrollFrameInfo.frameNo);
    if (GetInfoAdrs(0, 0) != 0) {
        MultiEventSet((u16 *)GetInfoAdrs(0, 0), 0, 0, 0);
    }
    MultiRoomSet();
    data_021348f4[data_0212c4c8] = 1;
    func_0208309c();
}
