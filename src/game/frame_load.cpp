#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/frame_load.h"

// FrameLoad_Select() (0x0204df84): loads the frame chosen by frame_select. Sets up the map data, the player start of
// the frame (MPlayerSet), the room and frame tables, the event lists of area 0 and the treasure list, and finally the
// extra parts when the game mode is below 5.
void FrameLoad_Select(void) {
    FRAME_INFO_ *frame;
    u32 partsFlags;
    FrameEntry *entry;

    entry = frame_select();
    frame = entry->frame;
    partsFlags = entry->flags;
    GameState_SetTrackVariant();
    if (gameState.unk_8e != 0) {
        CgLoad(2);
        DataLoad(0x10);
        *(u16 *)0x05000000 = 0;
        data_021355a0 = 0;
    }
    gameState.active = (frame->roomNo == 4) ? 1 : 0;
    data_02134968[0] = frame->infoRows;
    gameState.unk_49[3] = frame->unk_02[1];
    MPlayerSet(frame);
    MultiRoomInit(frame->roomNo);
    FrameSet(frame->frameNo);
    data_0213492c[1] = 0;
    data_0213492c[0] = data_0213492c[1];
    data_0213492c[2] = frame->unk_02[2] << 4;
    data_0213492c[3] = frame->unk_02[3] << 4;
    if (GetInfoAdrs(0, 0) != 0) {
        MultiEventSet((u16 *)GetInfoAdrs(0, 0), 0, 0, 0);
    }
    if (GetInfoAdrs(0, 1) != 0) {
        MultiEventSet((u16 *)GetInfoAdrs(0, 1), 0, 0, 0);
    }
    if (GetInfoAdrs(0, 3) != 0) {
        takara_set((u8 *)GetInfoAdrs(0, 3), frame, 0);
    }
    if (gameState.unk_01 < 5) {
        parts_set(frame, partsFlags);
    }
}
